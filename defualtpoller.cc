#include <stdlib.h>

#include "poller.h"
#include "epollpoller.h"

Poller* Poller::newDefaultPoller(EventLoop* loop)
{
    if (::getenv("MODUO_USE_POLL"))
    {
        return nullptr;
    }
    else
    {
        return new EPollPoller(loop);
    }
}