#include <cstdlib>
#include <linux/fs.h>
#include <ext2fs/ext2_fs.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <unistd.h>

#include "Formatter.h"

using namespace std;

Formatter* Formatter::formatter = nullptr; 

Formatter* Formatter::getFormatter(string path){
    if (!formatter){
        formatter = new Formatter(path);
    }
    return formatter;
}

void Formatter::format(){
    char boot[1024];
    ext2_super_block super_block;
    ext2_inode inode_table;
    ext2_group_desc first_block_descr;
}
