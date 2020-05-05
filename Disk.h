#ifndef DISK_H
#define DISK_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <ext2fs/ext2_fs.h>

#include "Logger.h"
#include "Exceptions.h"


class Disk{
    private:
        int fd; // File descriptor
        ext2_super_block sb; // Superblock
        ext4_group_desc bg; // Block descriptor
        Logger* logger = logger->getLogger(LogLevel::DEBUG);
        int getBlockSizeOffset();
    public:
        Disk(std::string path);
        ~Disk();
        void setPath(std::string path);
        std::string getPath();
        ext2_super_block readSuperBlock();
        ext4_group_desc readFirstBGD();
        ext2_inode readInode();
        void writeEmptyInodes();

};

#endif
