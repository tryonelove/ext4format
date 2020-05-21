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
        string path; // Drive path
        ext2_filsys fs; // Filesystem handle
        ext2_super_block fs_param; // Superblock params

        Logger* logger = logger->getLogger(LogLevel::DEBUG);
        void setSbParams();
    public:
        Disk(std::string path);

        // void erase();
        // void initialize();
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
