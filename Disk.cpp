#include <iostream>
#include <ext2fs/ext2fs.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "Disk.h"
#include <vector>

using namespace std;


Disk::Disk(string path){
    unix_io_manager ;
    ext2fs_open(path.c_str(), EXT2_FLAG_RW, 0, 0, unix_io_manager, &this->fs);
}

void Disk::clearInodes(){ 
    ext2_inode inode = {0};
    ext2fs_read_bitmaps(this->fs);
    ext2fs_clear_block_bitmap(this->fs->inode_map);
    long count = this->fs->super->s_inodes_count - this->fs->super->s_free_inodes_count;
    for(int i=12; i<=count; i++){
        ext2fs_write_inode(this->fs, i, &inode);
    }
    ext2fs_flush(this->fs);
    ext2fs_free(this->fs);
    ext2fs_close(this->fs);
}


Disk::~Disk(){

}