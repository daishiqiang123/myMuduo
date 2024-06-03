#pragma once
/*

*/
class NonCopable
{
public:
    NonCopable(const NonCopable&) = delete;
    NonCopable& operator=(const NonCopable&) = delete;
protected:
    NonCopable() = default;
    ~NonCopable() = default;
};