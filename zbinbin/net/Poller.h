#ifndef __ZBINBIN_POLLER_H_
#define __ZBINBIN_POLLER_H_

#include "zbinbin/utility/noncopyable.h"
#include "zbinbin/net/EventLoop.h"

#include <memory>
#include <vector>
#include <unordered_map>

#include <poll.h>

struct pollfd;

namespace zbinbin
{
class Channel;
class EventLoop;

class Poller : noncopyable
{
private:
    typedef std::unordered_map<int, Channel*> ChannelMap;
    typedef std::vector<Channel*> ChannelList;

public:
    Poller(EventLoop* loop);
    ~Poller();

    void poll(ChannelList* activeChannels);

    /// Changes the interested I/O events.
    /// Must be called in the loop thread.
    void updateChannel(Channel* channel);
    /// Remove the channel, when it destructs.
    /// Must be called in the loop thread.
    void removeChannel(Channel* channel);

private:


    void fillActiveChannels(int numEvents, ChannelList* activeChannels);

    void assertInLoopThread() { loop_->assertInLoopThread(); }

    EventLoop* loop_;
    ChannelMap channels_;
    std::vector<pollfd> pollfds_;
};

}   // namespace zbinbin


#endif  //__ZBINBIN_POLLER_H_