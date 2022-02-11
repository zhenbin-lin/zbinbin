#ifndef __ZBINBIN_EVENTLOOP_H_
#define __ZBINBIN_EVENTLOOP_H_
#include <memory>


namespace zbinbn
{
class Poller;
class Channel;

class EventLoop : std::enable_shared_from_this<Poller>
{
public:
    using ptr = std::shared_ptr<EventLoop>;

    EventLoop(/* args */);
    ~EventLoop();

    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);

    void loop();
    void quit();


private:


    bool looping_;
    bool quit_;

    const pid_t threadId_;
    std::unique_ptr<Poller> poller_;


};

using EventLoopPtr = std::shared_ptr<EventLoop>;




}   // namespace zbinbn

#endif  // __ZBINBIN_EVENTLOOP_H_