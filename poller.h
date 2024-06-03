#pragma once

#include<vector>
#include <unordered_map>
#include "noncopable.h"
#include "timestamp.h"

class Channel;
class EventLoop;

class Poller
{
public:
    using channelList = std::vector<Channel*>;

    Poller(EventLoop* loop);
    virtual ~Poller() = default;

    virtual TimeStamp poll(int timeOutMs, channelList* activateChannels) = 0;
    virtual void updateChannel(Channel* channel) = 0;
    virtual void removeChannel(Channel* channel) = 0;
    bool hasChannel(Channel* channel) const;
    // 这个要返回epoll的实例，但由于epoll是poller的派生类，你在基类的cc文件实现这个方法时
    // 就要包含epoll的文件，就是基类包含派生类，这样是不好的，所以另起了一个公共文件defualtpoller进行实现
    static Poller* newDefaultPoller(EventLoop* loop); 
protected:
    using channelMap = std::unordered_map<int, Channel*>;
    channelMap channels_;
private:
    EventLoop* ownerLoop_;
};