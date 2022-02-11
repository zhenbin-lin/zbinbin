#include "zbinbin/net/EventLoop.h"
#include "zbinbin/net/Poller.h"
#include "zbinbin/net/Channel.h"
#include "zbinbin/log/Logging.h"

// #include "Poller.h"

#include <poll.h>
#include <assert.h>

namespace zbinbin
{

__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop()
    : looping_(false)
    , quit_(false)
    , threadId_(CurrentThread::tid())
    , poller_(new Poller(this))
{
    LOG_TRACE << "EventLoop created " << this << " in thread " <<  threadId_;
    if (t_loopInThisThread)
    {
        LOG_FATAL << "Another EventLoop " << t_loopInThisThread
                  << " exists in this thread " << threadId_;
    }
    else
    {
        t_loopInThisThread = this;
    }
}

EventLoop::~EventLoop()
{
    assert(!looping_);
    t_loopInThisThread = NULL;
}

void EventLoop::updateChannel(Channel* channel)
{
    assert(channel->getOwerLoop() == this);
    assertInLoopThread();
    poller_->updateChannel(channel);    // 将channel注册到poller中
}

void EventLoop::removeChannel(Channel* channel)
{
    assert(channel->getOwerLoop() == this);
    assertInLoopThread();
    poller_->removeChannel(channel);
}

void EventLoop::loop()
{
    assert(!looping_);
    assertInLoopThread();
    looping_ = true;
    quit_ = false;

    while (!quit_) 
    {
        activeChannels_.clear();
        poller_->poll(&activeChannels_);
        for (auto& chptr : activeChannels_)
        {
            chptr->handleEvent();
        }
    }
    LOG_TRACE << "EventLoop " << this << " stop looping";
    looping_ = false;
}


void EventLoop::quit()
{
    quit_ = true;
}

EventLoop* getEventLoopOfCurrentThread()
{
    return t_loopInThisThread;
}


void EventLoop::abortNotInLoopThread()
{
    LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop " << this
              << " was created in threadId_ = " << threadId_
              << ", current thread id = " <<  CurrentThread::tid();
}



}   // namespace zbinbn