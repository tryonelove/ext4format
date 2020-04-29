#ifndef FORMATTER_H
#define FORMATTER_H

#include <iostream>
#include "Disk.h"

class Formatter {
    static Formatter* formatter;
    Disk* disk;
    Formatter(std::string path){
        this->disk = new Disk(path);
    };
    public:
        static Formatter* getFormatter(std::string path);
        void format();
};

#endif