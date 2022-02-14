#include "zbinbin/net/EventLoopThreadPool.h"
#include "zbinbin/net/EventLoopThread.h"
#include "zbinbin/net/EventLoop.h"


namespace zbinbin
{

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop,
                    size_t numThreads, 
                    const std::string& name)
    : started_(false)
    , baseLoop_(baseLoop)
    , name_(name)
    , numThreads_(numThreads)
    , nextLoop_(0)
    , threads_(numThreads)
    , ioLoops_(numThreads, nullptr)
{
}

EventLoopThreadPool::~EventLoopThreadPool()
{
    // Don't delete loop, it's stack variable
}

/// start all Threads
void EventLoopThreadPool::start(const ThreadInitCallback& cb)
{
    assert(!started_);
    started_ = true;
    for (int i = 0; i < numThreads_; ++i)
    {
        threads_[i].reset(new EventLoopThread(cb, name_ + "-" + std::to_string(i)));
        ioLoops_[i] = threads_[i]->startLoop();
    }
    if (numThreads_ == 0 && cb)
    {
        cb(baseLoop_);
    }
}

// void setThreadNum(int numThreads);
// valid after calling start()
/// round-robin
EventLoop* EventLoopThreadPool::getNextLoop()
{
    baseLoop_->assertInLoopThread();
    assert(started_);
    EventLoop* loop = baseLoop_;
    if (!ioLoops_.empty())
    {
        loop = ioLoops_[nextLoop_];
        ++nextLoop_;
        nextLoop_ %= numThreads_;
    }
    return loop;
}

}
