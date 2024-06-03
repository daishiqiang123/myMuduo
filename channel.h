#pragma once

#include <memory>
#include <functional>

#include "noncopable.h"
#include "timestamp.h"


class EventLoop;
class TimeStamp;
/**
 * 理清楚  EventLoop、Channel、Poller之间的关系   《= Reactor模型上对应 Demultiplex
 * Channel 理解为通道，封装了sockfd和其感兴趣的event，如EPOLLIN、EPOLLOUT事件
 * 还绑定了poller返回的具体事件
 */ 
class Channel : private NonCopable
{
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(TimeStamp)>;

    // 这里的EventLoop可以用类的前置声明使用（不在h中包含头文件，在cc中包含头文件），因为参数是指针，4字节，不影响编译
    Channel(EventLoop* loop, int fd); 
    ~Channel();      

    // 这里必须包含相应头文件，因为用的类  fd得到poller通知以后，处理事件的函数
    void handleEvent(TimeStamp receiveTime);
    
    // 因为认为函数对象较大 所以才用了move变成右值，进行构造
    void setReadCallback(ReadEventCallback rcb){readCallback_ = std::move(rcb);}
    void setWriteCallback(EventCallback cb){writeCallback_ = std::move(cb);}
    void setCloseCallback(EventCallback cb){closeCallback_ = std::move(cb);}
    void setErrorCallback(EventCallback cb){errorCallback_ = std::move(cb);}

    // 防止当channel被手动remove掉，channel还在执行回调操作
    void tie(const std::shared_ptr<void>&);
    
    int fd() const {return fd_;}
    int events() const {return events_;}
    void set_revents(int revt) {events_ = revt;}


    // 设置fd相应的事件状态  |=按位或：类似添加操作  &= ~按位与：类似删除操作
    void enableReading(){ events_ |= kReadEvent; update();}
    void disableReading(){ events_ &= ~kReadEvent; update();}
    void enableWriting(){ events_ |= kWriteEvent; update();}
    void disableWriting(){ events_ &= ~kWriteEvent; update();}
    void disableAll() { events_ &= kNoneEvent; update();}

    bool isNoneEvent() const {return events_ == kNoneEvent;}
    bool isWriting() const {return events_ & kWriteEvent;}
    bool isReading() const {return events_ & kReadEvent;}

    int index() { return index_;};
    void set_index(int idx) { index_ = idx;}

    EventLoop* ownerLoop() { return loop_;}
    void remove();
    void update();

private:

    
    void handleEventWithGuard(TimeStamp receiveTime);

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop* loop_;
    const int fd_;
    int events_;
    int revents_;
    int index_;

    std::weak_ptr<void> tie_;
    bool tied_;
    // 因为channel通道里面能够获知fd最终发生的具体的事件revents，所以它负责调用具体事件的回调操作
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};