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

    @param path Path to the partition which has to be formatted.
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
    */
    this->disk->allocateTables();
    this->disk->writeInodeTable();
    this->disk->createRootDir();
    this->disk->createLostAndFound();
    this->disk->reserveInodes();
    this->disk->closeDisk();
}
