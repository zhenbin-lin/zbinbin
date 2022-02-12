#ifndef __ZBINBIN_EVENTLOOP_H_
#define __ZBINBIN_EVENTLOOP_H_

#include "zbinbin/utility/noncopyable.h"
#include "zbinbin/thread/CurrentThread.h"
#include "zbinbin/thread/Mutex.h"

#include <memory>
#include <vector>
#include <functional>

namespace zbinbin
{
class Acceptor;
class Poller;
class Channel;

class EventLoop : std::enable_shared_from_this<Poller>
                , noncopyable
{
public:
    using Functor = std::function<void()>;
    using ptr = std::shared_ptr<EventLoop>;

    EventLoop();
    ~EventLoop();

    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);

    void loop();
    void quit();

    void assertInLoopThread();

    bool isInLoopThread() { return threadId_ == CurrentThread::tid(); }

    void runInLoop(Functor cb);

    static EventLoop* getEventLoopOfCurrentThread();
private:
    typedef std::vector<Channel*> ChannelList;

    void abortNotInLoopThread();
    void queueInLoop(Functor cb);
    void doPendingFunctors();
    void wakeup();
    void handleRead();

    bool looping_;
    bool quit_;
    bool eventHandling_;
    bool callingPendingFunctors_;
    const pid_t threadId_;
    const int wakeupFd_;
    std::unique_ptr<Poller> poller_;
    std::unique_ptr<Channel> wakeupChannel_;    // don't expose Channel to client
    ChannelList activeChannels_;
    
    mutable MutexLock mutex_;   // 在const对象或者const方法中仍然可变
    std::vector<Functor> pendingFunctors_;
};


inline void EventLoop::assertInLoopThread()
{
    if (!isInLoopThread())
    {
        abortNotInLoopThread();
    }
}




using EventLoopPtr = std::shared_ptr<EventLoop>;

}   // namespace zbinbn

#endif  // __ZBINBIN_EVENTLOOP_H_