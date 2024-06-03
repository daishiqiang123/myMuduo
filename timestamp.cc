#include "timestamp.h"

TimeStamp::TimeStamp(): microSecondSinceEpoch_(0){}
TimeStamp::TimeStamp(int64_t microSecondSinceEpoch) : microSecondSinceEpoch_(microSecondSinceEpoch){}
TimeStamp TimeStamp::now()
{
    return TimeStamp(time(nullptr));
}
std::string TimeStamp::toString()
{
    char buf[128] = {0};
    tm* tm_time = localtime(&microSecondSinceEpoch_);
    snprintf(buf, 128, "%4d/%02d/%02d %02d:%02d:%02d",
                        tm_time->tm_year + 1900,
                        tm_time->tm_mon + 1,
                        tm_time->tm_mday,
                        tm_time->tm_hour,
                        tm_time->tm_min,
                        tm_time->tm_sec);
    return buf; // 这里发生了string构造的隐式转换
}


/*
#include<iostream>
int main()
{
    std::cout << TimeStamp::now().toString() << std::endl;
    return 0;
}
*/
