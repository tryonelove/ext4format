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
        const char* path;
        ext2_filsys fs; // Filesystem handle
        ext2_super_block fs_param;
        int block_size_offset; // block size offset

        Logger* logger = logger->getLogger(LogLevel::DEBUG);

    public:
        Disk(std::string path);
        void allocateTables();
        
        void clearBlockDescriptors();

        void writeInodeTable();
        void writeReservedInodes();

        void reserveInodes();
        void createRootDir();
        void createLostAndFound();

        void readInodes();
        void clearBitmaps();
        void clearInodes();
        void closeDisk();
};

#endif
