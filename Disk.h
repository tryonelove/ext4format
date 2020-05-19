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
        ext2_filsys fs; // Filesystem handle
        int block_size_offset; // block size offset

        Logger* logger = logger->getLogger(LogLevel::DEBUG);

    public:
        Disk(std::string path);
        void clearBlockDescriptors();
        void writeReservedInodes();
        void readInodes();
        void clearBitmaps();
        void clearInodes();
        void closeDisk();
};

#endif
