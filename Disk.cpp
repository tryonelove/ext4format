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
    ext2fs_open(path.c_str(), EXT2_FLAG_RW, 0, 0, unix_io_manager, &this->fs);
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
    ext2fs_mark_bb_dirty(this->fs);

    this->logger->info("Clearing inode bitmap.");
    ext2fs_clear_inode_bitmap(this->fs->inode_map);
    ext2fs_mark_ib_dirty(this->fs);
    this->logger->success();
}

void Disk::clearInodes(){
    ext2_ino_t i_inode;
    ext2_ino_t i_inode2;
    ext2_inode inode = {0};
    blk_t blk;
    int count = this->fs->super->s_inodes_count - this->fs->super->s_free_inodes_count;
    this->logger->info("Clearing inodes...");
    for(i_inode=12; i_inode<=count; i_inode++){
        ext2fs_write_inode(this->fs, i_inode, &inode);
        this->fs->super->s_free_inodes_count++;
    }
    this->logger->success();
}

void Disk::closeDisk(){
    ext2fs_flush(this->fs);
    ext2fs_free(this->fs);
    ext2fs_close(this->fs);
}