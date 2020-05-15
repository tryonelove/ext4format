#ifndef DISK_H
#define DISK_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <ext2fs/ext2fs.h>

#include "Logger.h"
#include "Exceptions.h"


class Disk{
    private:
        ext2_filsys fs; // File descriptor
        ext2_super_block sb; // Superblock
        ext4_group_desc bg; // Block descriptor
        int block_size_offset; // block size offset

        Logger* logger = logger->getLogger(LogLevel::DEBUG);

    public:
        Disk(std::string path);
        ~Disk();

        void clearInodes();
};

#endif
