#pragma once

#include<iostream>

#include "noncopable.h"
class TimeStamp
{
public:
    TimeStamp();
    explicit TimeStamp(int64_t microSecondSinceEpoch);
    static TimeStamp now();
    std::string toString();
private:
    int64_t microSecondSinceEpoch_;
};