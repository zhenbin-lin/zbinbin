
#include "EventLoop.h"
#include "Poller.h"
#include <assert.h>

namespace zbinbn
{

EventLoop::EventLoop(/* args */)
{
}

EventLoop::~EventLoop()
{
}

void EventLoop::updateChannel(Channel* channel)
{
}
void EventLoop::removeChannel(Channel* channel)
{
}

void EventLoop::loop()
{
    assert(!looping_);
    looping_ = true;
    quit_ = false;

    while (!quit_) 
    {
        poller_->poll();
    }
}


void EventLoop::quit()
{

}





}   // namespace zbinbn