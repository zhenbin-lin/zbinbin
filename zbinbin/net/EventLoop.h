#ifndef __ZBINBIN_EVENTLOOP_H_
#define __ZBINBIN_EVENTLOOP_H_

#include "zbinbin/utility/noncopyable.h"
#include "zbinbin/thread/CurrentThread.h"


#include <memory>
#include <vector>

namespace zbinbin
{
class Poller;
class Channel;

class EventLoop : std::enable_shared_from_this<Poller>
                , noncopyable
{
public:
    using ptr = std::shared_ptr<EventLoop>;

    EventLoop(/* args */);
    ~EventLoop();

    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);

    void loop();
    void quit();


    bool isInLoopThread() { return threadId_ == CurrentThread::tid(); }

    void assertInLoopThread();

    static EventLoop* getEventLoopOfCurrentThread();
private:
    typedef std::vector<Channel*> ChannelList;

    void abortNotInLoopThread();

    bool looping_;
    bool quit_;
    const pid_t threadId_;
    std::unique_ptr<Poller> poller_;
    ChannelList activeChannels_;
    
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