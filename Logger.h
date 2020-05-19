#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

enum LogLevel {
    INFO,
    WARN,
    ERROR,
    DEBUG
};

class Logger{
    static Logger* logger;
    LogLevel level;
    Logger(LogLevel level){
        this->level = level;
    };
    public:
        static Logger* getLogger(LogLevel level = DEBUG);
        ~Logger();
        void info(std::string message);
        void debug(std::string message);
        void error(std::string message);
        void warn(std::string message);
        void success();
        void setLevel(LogLevel level);
};

#endif