#include "zbinbin/net/EventLoop.h"
#include "zbinbin/net/SocketOps.h"
#include "zbinbin/net/Poller.h"
#include "zbinbin/net/Channel.h"
#include "zbinbin/log/Logging.h"

#include <poll.h>
#include <assert.h>
#include <functional>

#include <sys/eventfd.h>    // eventfd
#include <unistd.h>         // ::close()

namespace zbinbin
{

namespace detail
{

inline void destoryEventfd(int evtfd)
{
    ::close(evtfd);
}

int createEventfd()
{
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0)
    {
        LOG_SYSERR << "Failed in eventfd";
        abort();
    }
    return evtfd;
}

}   // namespace detail

__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop()
    : looping_(false)
    , quit_(false)
    , eventHandling_(false)
    , callingPendingFunctors_(false)
    , threadId_(CurrentThread::tid())
    , wakeupFd_(detail::createEventfd())
    , poller_(new Poller(this))
    , wakeupChannel_(new Channel(this, wakeupFd_))
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
    wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead, this));
    wakeupChannel_->enableReading();
}

EventLoop::~EventLoop()
{
    LOG_DEBUG << "EventLoop " << this << " of thread " << threadId_
              << " destructs in thread " << CurrentThread::tid();
    assert(!looping_);
    t_loopInThisThread = NULL;
    wakeupChannel_->disableAll();
    wakeupChannel_->remove();
    detail::destoryEventfd(wakeupFd_);
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
        eventHandling_ = true;
        for (auto& chptr : activeChannels_)
        {
            chptr->handleEvent();
        }
        doPendingFunctors();
        eventHandling_ = false;
    }
    LOG_TRACE << "EventLoop " << this << " stop looping";
    looping_ = false;
}


void EventLoop::quit()
{
    quit_ = true;
    // 如果在LoopThread，则说明现在不在while(!quit_)中
    // 因此不需要调用wakeup让EventLoop从Poller中被唤醒
    if (!isInLoopThread())
    {
        wakeup();
    }
}


void EventLoop::runInLoop(Functor cb)
{
    if (isInLoopThread()) 
    {
        cb();
    }
    else
    {
        queueInLoop(std::move(cb));
    }
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


void EventLoop::queueInLoop(Functor cb)
{
    {
    MutexLockGuard lock(mutex_);
    pendingFunctors_.push_back(std::move(cb));
    }

    if (!isInLoopThread() || callingPendingFunctors_)
    {
        wakeup();
    }
}


void EventLoop::doPendingFunctors()
{
    std::vector<Functor> functors;
    callingPendingFunctors_ = true;
    {
    MutexLockGuard lock(mutex_);
    functors.swap(pendingFunctors_);
    }

    for (const Functor& functor : functors)
    {
        functor();
    }
    callingPendingFunctors_ = false;
}


void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t n = sockets::write(wakeupFd_, &one, sizeof one);
    if (n != sizeof one)
    {
        LOG_ERROR << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
    }
}


void EventLoop::handleRead()
{  
    uint64_t one = 1;
    ssize_t n = sockets::read(wakeupFd_, &one, sizeof one);
    if (n != sizeof one)
    {
        LOG_ERROR << "EventLoop::handleRead() reads " << n << " bytes instead of 8";
    }
}


}   // namespace zbinbn