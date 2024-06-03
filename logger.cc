#include<iostream>

#include"logger.h"
#include "timestamp.h"
Logger& Logger::getInstance()
{
    static Logger log;
    return log;
}
void Logger::setLogLevel(int level)
{
    logLevel_ = level;
}
void Logger::log(const std::string& msg)
{
    switch (logLevel_)
    {
    case INFO:
        std::cout << "INFO" << std::endl;
        break;
    case ERROR:
        std::cout << "ERROR" << std::endl;
        break;
    case FATAL:
        std::cout << "FATAL" << std::endl;
        break;
    case DEBUG:
        std::cout << "DEBUG" << std::endl;
        break;
    default:
        break;
    }
    std::cout << TimeStamp::now().toString() << " : " << msg << std::endl;
}