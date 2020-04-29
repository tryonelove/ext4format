#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include "Disk.h"

using namespace std;

Disk::Disk(string path){
    try{
        if(this->fd = open(path.c_str(), O_RDONLY) == -1){
            throw new CantOpenDevice;
        }
    } catch (CantOpenDevice& openError){
        logger->error(openError.what());
    }
}

void Disk::setPath(string path){
    this->path = path;
}

string Disk::getPath(){
    return this->path;
}

int Disk::open(){
    read(fd, &boot, 1024);
    read(fd, &super_block, sizeof(ext2_super_block));
    lseek(fd, 4096, SEEK_SET);
    read(fd, &first_block_descr, sizeof(ext2_group_desc));
}