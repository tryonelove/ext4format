#include <iostream>
#include "Logger.h"

Logger* Logger::logger = nullptr;

Logger* Logger::getLogger(LogLevel level){
    /*
    Returns a logger instance.

    @param level LogLevel variable that defines
    logging level.

    @return Logger class instance.
    */
    if (!logger){
        logger = new Logger(level);
    }
    return logger;
}

void Logger::setLevel(LogLevel level){
    this->level = level;
}

void Logger::info(std::string message){
    if(this->level < INFO) return;
    std::cout << "INFO: " << message << std::endl; 
}

void Logger::debug(std::string message){
    if(this->level < DEBUG) return;
    std::cout << "DEBUG: " << message << std::endl; 
}

void Logger::error(std::string message){
    if(this->level < ERROR) return;
    std::cout << "ERROR: " << message << std::endl; 
}

void Logger::warn(std::string message){
    if(this->level < WARN) return;
    std::cout << "WARN: " << message <<std::endl;
}

void Logger::success(){
    std::cout << "Success!" << std::endl;
}

Logger::~Logger(){
    delete logger;
}
