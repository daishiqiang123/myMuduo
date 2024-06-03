#pragma once
#include<string>
#include"noncopable.h"

#define LOG_INFO(LogmsgFormat, ...) \
    do \
    { \
        Logger& logger = Logger::getInstance(); \
        logger.setLogLevel(INFO); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, LogmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } \
    while(0) 

#define LOG_ERROR(LogmsgFormat, ...) \
    do \
    { \
        Logger& logger = Logger::getInstance(); \
        logger.setLogLevel(ERROR); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, LogmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } \
    while(0) 

#define LOG_FATAL(LogmsgFormat, ...) \
    do \
    { \
        Logger& logger = Logger::getInstance(); \
        logger.setLogLevel(FATAL); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, LogmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
        exit(-1); \
    } \
    while(0) 

#ifdef MODEDEBUG
#define LOG_DEBUG(LogmsgFormat, ...) \
    do \
    { \
        Logger& logger = Logger::getInstance(); \
        logger.setLogLevel(DEBUG); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, LogmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } \
    while(0) 
#else
    #define LOG_DEBUG(LogmsgFormat, ...)
#endif

// 定义日志的级别 INFO ERROR FATAL DEBUG
enum logLevel
{
    INFO ,
    ERROR, 
    FATAL,
    DEBUG
};

class Logger : private NonCopable
{
public:
    static Logger& getInstance();
    void setLogLevel(int level);
    void log(const std::string& msg);
private:
    int logLevel_;
    Logger(){}
};
