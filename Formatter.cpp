#include <cstdlib>
#include <linux/fs.h>
#include "ext2fs/ext2_fs.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>

#include "Formatter.h"

// int fd;
// char boot[1024];
// ext2_super_block super_block;
// ext2_inode inode_table;
// ext2_group_desc first_block_descr;
// fd = open("/dev/sdc1", O_RDONLY);
// read(fd, &boot, 1024);
// read(fd, &super_block, sizeof(ext2_super_block));
// lseek(fd, 4096, SEEK_SET);
// read(fd, &first_block_descr, sizeof(ext2_group_desc));
// close(fd);

using namespace std;

Formatter* Formatter::getFormatter(){
    if (!formatter)
    formatter = new Formatter;
    return formatter;
}

void Formatter::setPath(string path){
    this->formatPath = path;
}

string Formatter::getPath(){
    return this->formatPath;
}

