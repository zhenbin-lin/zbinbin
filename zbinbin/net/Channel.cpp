#include "zbinbin/net/Channel.h"
#include "zbinbin/net/EventLoop.h"
#include "zbinbin/log/Logging.h"



#include <sstream>

#include <poll.h>
#include <assert.h>


namespace zbinbin
{

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;


Channel::Channel(EventLoop* loop, int fd)
    : eventHandling_(false)
    , addedToLoop_(false)
    , loop_(loop)
    , fd_(fd)
    , events_(0)
    , revents_(0)
    , index_(-1)
{
}

Channel::~Channel()
{

}

void Channel::handleEvent()
{
    eventHandling_ = true;
    if (revents_ & POLLNVAL) 
    {
        LOG_WARN << "Channel::handle_event() POLLNVAL";
    }

    if ((revents_ & POLLHUP) && !(revents_ & POLLIN)) 
    {
        LOG_WARN << "Channel::handle_event() POLLHUP";
        if (closeCallback_) closeCallback_();
    }
    if (revents_ & (POLLERR | POLLNVAL)) 
    {
        if (errorCallback_) errorCallback_();
    }
    if (revents_ & (POLLIN | POLLPRI | POLLRDHUP)) 
    {
        if (readCallback_) readCallback_(/* receiveTime */);
    }
    if (revents_ & POLLOUT) 
    {
        if (writeCallback_) writeCallback_();
    }
    eventHandling_ = false;
}

void Channel::remove()
{
    assert(isNoneEvents());
    addedToLoop_ = false;
    loop_->removeChannel(this);
}

void Channel::update()
{
    loop_->updateChannel(this);
}



}   // namespace zbinbin