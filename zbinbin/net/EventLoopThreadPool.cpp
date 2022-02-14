#include "zbinbin/net/EventLoopThreadPool.h"
#include "zbinbin/net/EventLoopThread.h"
#include "zbinbin/net/EventLoop.h"


namespace zbinbin
{

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop,
                    const std::string& name)
    : started_(false)
    , baseLoop_(baseLoop)
    , name_(name)
    , numThreads_(0)
    , nextLoop_(0)
{
    // , threads_(0)
    // , ioLoops_(0, nullptr)
    // use default ctor
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
    threads_.resize(numThreads_);
    ioLoops_.resize(numThreads_);
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

void EventLoopThreadPool::setThreadNum(int numThreads) 
{ 
    assert(!started_);
    assert(0 <= numThreads);
    numThreads_ = numThreads; 
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
