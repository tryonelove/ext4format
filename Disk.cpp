#include <iostream>
#include <ext2fs/ext2fs.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <vector>
#include <sys/stat.h>
#include "Disk.h"

using namespace std;


Disk::Disk(string path){
	this->path = path.c_str();
}

void Disk::allocateTables(){
    errcode_t	retval;

	this->logger->info("Allocationg tables.");

	initialize_ext2_error_table();

	this->logger->info("Succesfuly initialized error table.");
	memset(&this->fs_param, 0, sizeof(this->fs_param));

	ext2fs_blocks_count_set(&this->fs_param, 7569399*4);

	this->fs_param.s_feature_incompat |= EXT4_FEATURE_INCOMPAT_INLINE_DATA;

	retval = ext2fs_initialize("/dev/sdd1", EXT2_FLAG_PRINT_PROGRESS, &this->fs_param,
				   unix_io_manager, &this->fs);
	ext2fs_mark_super_dirty(this->fs); 
	if (retval) {
		this->logger->error("Error while initializing filesystem");
		exit(1);
	}
	retval = ext2fs_allocate_tables(this->fs);
	if (retval) {
		this->logger->error("Error while allocating tables for filesystem");
		exit(1);
    }
}

void Disk::writeReservedInodes(){
	errcode_t retval;
	ext2_ino_t ino;
	struct ext2_inode *inode;

	this->logger->info("Writing reserved inodes.");

	retval = ext2fs_get_memzero(EXT2_INODE_SIZE(this->fs->super), &inode);
	if (retval) {
		this->logger->error("While allocating memory");
		exit(1);
	}

	for (ino = 1; ino < EXT2_FIRST_INO(fs->super); ino++) {
		retval = ext2fs_write_inode_full(fs, ino, inode,
						 EXT2_INODE_SIZE(fs->super));
	}
	ext2fs_free_mem(&inode);
	this->logger->success();
}

void Disk::createRootDir(){
    errcode_t retval;
	ext2_inode inode;

	this->logger->info("Creating root dir.");

	retval = ext2fs_mkdir(fs, EXT2_ROOT_INO, EXT2_ROOT_INO, 0);
	if (retval) {
		this->logger->error("Error while creating root dir");
		exit(1);
	}

	if (getuid()) {
		retval = ext2fs_read_inode(this->fs, EXT2_ROOT_INO, &inode);
		if (retval) {
			this->logger->error("Error while writing root dir");
			exit(1);
		}

		inode.i_uid = getuid();
		if (inode.i_uid)
			inode.i_gid = getgid();
		retval = ext2fs_write_new_inode(fs, EXT2_ROOT_INO, &inode);
		if (retval) {
            this->logger->error("Error while setting inode owner");
			exit(1);
		}
	}
	this->logger->success();
}

void Disk::createLostAndFound(){
	/*
	Method to create lost+found directory
	*/
    unsigned int lpf_size = 0;
	errcode_t retval;
	ext2_ino_t ino;
	const char *name = "lost+found";
	int	i;
	this->fs->umask = 077;

	this->logger->info("Creating lost+found directory.");

	retval = ext2fs_mkdir(this->fs, EXT2_ROOT_INO, 0, name);
	if (retval) {
		this->logger->error("Error while creating lost+found");
		exit(1);
	}

	retval = ext2fs_lookup(fs, EXT2_ROOT_INO, name, strlen(name), 0, &ino);
	if (retval) {
		this->logger->error("Error while looking up /lost+found");
		exit(1);
	}

	for (i=1; i < EXT2_NDIR_BLOCKS; i++) {
		/* Ensure that lost+found is at least 2 blocks, so we always
		 * test large empty blocks for big-block filesystems.  */
		if ((lpf_size += fs->blocksize) >= 16*1024 &&
		    lpf_size >= 2 * fs->blocksize)
			break;
		retval = ext2fs_expand_dir(fs, ino);
		if (retval) {
			this->logger->error("Error while expanding /lost+found");
			exit(1);
		}
	}
	this->logger->success();
}

void Disk::clearBitmaps(){
    /*
    Method to clean all bitmaps (e.g. inode and block)
    */
    int retval;
    this->logger->info("Reading bitmaps.");
    retval = ext2fs_read_bitmaps(this->fs);
    if(retval){
        this->logger->error("Can't read filesystem bitmaps.");
        exit(-1);
    }
    this->logger->info("Clearing block bitmap.");
    ext2fs_clear_block_bitmap(this->fs->block_map);
    this->logger->success();
    this->logger->info("Clearing inode bitmap.");
    ext2fs_clear_inode_bitmap(this->fs->inode_map);
    this->logger->success();
}

void Disk::writeInodeTable(){
    errcode_t retval;
	blk64_t	blk;
	dgrp_t	i;
	int	num;
	this->logger->info("Writing inode tables");

	for (i = 0; i < this->fs->group_desc_count; i++) {
		blk = ext2fs_inode_table_loc(fs, i);
		num = ext2fs_div_ceil((fs->super->s_inodes_per_group -
					       ext2fs_bg_itable_unused(fs, i)) *
					      EXT2_INODE_SIZE(fs->super),
					      EXT2_BLOCK_SIZE(fs->super));
        ext2fs_bg_flags_set(fs, i, EXT2_BG_INODE_ZEROED);
		ext2fs_zero_blocks2(fs, blk, num, &blk, &num);
	}

	if (ext2fs_has_feature_metadata_csum(this->fs->super))
		writeReservedInodes();
    this->logger->success();
}

void Disk::reserveInodes(){
	ext2_ino_t	i;
	for (i = EXT2_ROOT_INO + 1; i < EXT2_FIRST_INODE(this->fs->super); i++)
		ext2fs_inode_alloc_stats2(this->fs, i, +1, 0);
	ext2fs_mark_ib_dirty(fs);
}


void Disk::closeDisk(){
    ext2fs_flush(this->fs);
	ext2fs_close_free(&this->fs);
	this->logger->info("Done with updating the drive.");
}