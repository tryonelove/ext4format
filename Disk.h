#ifndef DISK_H
#define DISK_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>

#include "Logger.h"
#include "Exceptions.h"


class Disk{
    int fd;
    Logger* logger = logger->getLogger(LogLevel::DEBUG);
    public:
        Disk(std::string path);
        void setPath(std::string path);
        std::string getPath();
};

#endif
