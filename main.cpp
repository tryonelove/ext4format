#include "Logger.h"
#include "Formatter.h"
#include <ext2fs/ext2_fs.h>


using namespace std;

void usage(){
    cout << "Usage: ./format /dev/sdxY" << endl;
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        usage();
        exit(-1);
    }
    Formatter* formatter = formatter->getFormatter(argv[1]);
    formatter->format();
    return 0;
}