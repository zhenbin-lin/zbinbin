#ifndef __ZBINBIN_CHANNEL_H_
#define __ZBINBIN_CHANNEL_H_
#include "zbinbin/net/EventLoop.h"
#include <memory>
#include <functional>

class Channel
{
class EventLoop;
public:
    using EventLoopPtr = std::shared_ptr<EventLoop>;
    using EventCallback = std::function<void()>;

    Channel(EventLoopPtr loop, int fd);
    ~Channel();

private:
    EventLoopPtr owerLoop_;

};


#endif  //__ZBINBIN_CHANNEL_H_