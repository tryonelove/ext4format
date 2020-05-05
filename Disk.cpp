#include <iostream>
#include <ext2fs/ext2_fs.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "Disk.h"

using namespace std;

Disk::Disk(string path){
    try{
        this->fd = open(path.c_str(), O_RDWR);
        if(this->fd == -1) throw new CantOpenDevice;
    } catch (CantOpenDevice& openError){
        logger->error(openError.what());
    }
}

ext2_super_block Disk::readSuperBlock(){
    /*
    Method to read the superblock.

    @return ext2_super_block structure
    */
    lseek(this->fd, 1024, SEEK_SET); // 1024 - Group 0 Padding 
    read(this->fd, &this->sb, sizeof(ext2_super_block));
    this->logger->debug("Succesfully read superblock.");
    return this->sb;
}

ext4_group_desc Disk::readFirstBGD(){
    /*
    Method to read a block group descriptor.

    @return ext4_group_desc structure
    */
    int block_size_offset = this->getBlockSizeOffset();
    lseek(this->fd, block_size_offset, SEEK_SET);
    read(this->fd, &this->bg, sizeof(ext4_group_desc));
    this->logger->debug("Succesfully read a group descriptor.");
    return this->bg;
}


// DOESN'T WORK, TO REWRITE
// void Disk::writeEmptyInodes(){
//     ext2_inode inode = {0};
//     int block_size_offset = this->getBlockSizeOffset();
//     int inodes_to_clean = this->sb.s_inodes_count - this->sb.s_free_inodes_count;
//     for(int i=1; i < inodes_to_clean; i++){
//         write(this->fd, &inode, sizeof(inode));
//     }
// }



int Disk::getBlockSizeOffset(){
    return 1024 << this->sb.s_log_block_size;
}

ext2_inode Disk::readInode(){
    ext2_inode inode;
    int block_size_offset = this->getBlockSizeOffset();
    read(this->fd, &inode, sizeof(ext2_inode));
    return inode;
}


Disk::~Disk(){
    close(this->fd);
    delete logger;
}