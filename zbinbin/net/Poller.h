#ifndef __ZBINBIN_POLLER_H_
#define __ZBINBIN_POLLER_H_
#include "zbinbin/utility/noncopyable.h"
#include <memory>
#include <vector>
#include <poll.h>

struct pollfd;

namespace zbinbin{
class Channel;
class EventLoop;

class Poller : noncopyable, 
{

public:
    Poller();
    ~Poller();

    void poll();

    /// Changes the interested I/O events.
    /// Must be called in the loop thread.
    void updateChannel(Channel* channel);
    /// Remove the channel, when it destructs.
    /// Must be called in the loop thread.
    void removeChannel(Channel* channel);

private:
    EventLoop* ownerLoop_;
    std::vector<pollfd> pollfds_;
};

}


#endif  //__ZBINBIN_POLLER_H_