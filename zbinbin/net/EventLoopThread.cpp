#include "zbinbin/thread/EventLoopThread"
#include "zbinbin/net/EventLoop.h"


namespace zbinbin
{

EventLoopThread::EventLoopThread(const ThreadInitCallback& cb, 
                                 const std::string& name)
    : loop_(nullptr)
    , thread_(std::bind(&EventLoopThread::threadFunc, this), name)
    , mutex_()
    , cond_(mutex_)
    , initCallback_(cb)
{
}


EventLoopThread::~EventLoopThread()
{
    if (loop_ != nullptr)
    {
        loop_.quit();
        thread_.join();
    }
}

EventLoop* EventLoopThread::startLoop()
{
    assert(!thread_.started());
    thread_.start();

    EventLoop* loop = nullptr;
    {
        MutexLockGurad lock(mutex_);
        while (loop_ != nullptr)
        {
            cond_.wait();
        }
        loop = &loop_;
    }
    return loop;
}

void EventLoopThread::threadFunc()
{
    EventLoop loop;
    if (initCallback_)
    {
        initCallback_(loop);
    }
    {
    MutexLockGuard lock(mutex_);
    loop_ = &loop;
    cond_.notify();
    }
    loop.loop();

    MutexLockGuard lock(mutex_);
    loop_ = nullptr;
}

}