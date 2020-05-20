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
        const char* path; // Partition path
        ext2_filsys fs; // Filesystem handle
        ext2_super_block sb; // Superblock

        Logger* logger = logger->getLogger(LogLevel::DEBUG);

    public:
        Disk(std::string path);
        void initialize();
        void allocateTables();
        
        void clearBlockDescriptors();

        void writeInodeTable();
        void writeReservedInodes();

        void reserveInodes();
        void createRootDir();
        void createLostAndFound();

        void clearBitmaps();
        void closeDisk();
};

#endif
