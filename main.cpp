#include "Logger.h"
#include "Formatter.h"
#include <ext2fs/ext2_fs.h>


using namespace std;

int main(int argc, char* argv[]) {
    Logger* logger = logger->getLogger(LogLevel::DEBUG);
    if(argc < 2) {
        logger->error(
        "Not enough args:\n \
        Usage: ./format /dev/sdxY");
        exit(-1);
    }
    Formatter* formatter = formatter->getFormatter(argv[1]);
    formatter->format();
    return 0;
}