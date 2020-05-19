#include <cstdlib>
#include <linux/fs.h>
#include <ext2fs/ext2fs.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <vector>

#include "Formatter.h"

using namespace std;

Formatter* Formatter::formatter = nullptr; 

Formatter* Formatter::getFormatter(string path){
    /*
    Get instance of Formatter class

    @param path Path to format.
    @return Formatter* instance.
    */
    if (!formatter){
        formatter = new Formatter(path);
    }
    return formatter;
}

void Formatter::format(){
    /*
    Main formatting function

    @return Void
    */
    this->disk->clearInodes();
    this->disk->clearBitmaps();
    this->disk->closeDisk();
}
