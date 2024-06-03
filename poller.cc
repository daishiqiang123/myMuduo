#include "poller.h"
#include "channel.h"
Poller::Poller(EventLoop* loop)
{
    ownerLoop_ = loop;
}

bool Poller::hasChannel(Channel* channel) const
{
    channelMap::const_iterator it = channels_.begin();
    it = channels_.find(channel->fd());
    if (it != channels_.end() && it->second == channel) return true;
    return false;
}