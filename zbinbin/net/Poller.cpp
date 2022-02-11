#include "zbinbin/net/Poller.h"
#include "zbinbin/net/Channel.h"
#include "zbinbin/log/Logging.h"

#include <assert.h>
#include <algorithm>


namespace zbinbin
{

Poller::Poller(EventLoop* loop)
    : loop_(loop)
{
}

Poller::~Poller()
{
}

void Poller::poll(ChannelList* activeChannels)
{
   int numEvents = ::poll(pollfds_.data(), pollfds_.size(), 50);
   int savedErrno = errno;

    if (numEvents > 0)
    {
        LOG_TRACE << numEvents << " events happened";
        fillActiveChannels(numEvents, activeChannels);
    }
    else if (numEvents == 0) 
    {
        LOG_TRACE << " nothing happened";
    }
    else 
    {
        if (savedErrno != EINTR)
        {
            errno = savedErrno;
            LOG_SYSERR << "Poller::poll()";
        }
    }

}


void Poller::fillActiveChannels(int numEvents, ChannelList* activeChannels)
{
    for (auto& pfd : pollfds_)
    {
        if (pfd.revents > 0)
        {
            --numEvents;
            Channel* channel = channels_[pfd.fd];
            assert(channel);
            channel->setRevents(pfd.revents);
            activeChannels->push_back(channel);
        }
    }
}

void Poller::updateChannel(Channel* channel)
{
    LOG_TRACE << "fd = " << channel->getFd() << " events = " << channel->getIndex();
    if (channel->getIndex() < 0)
    {
        struct pollfd pfd;
        pfd.fd =  channel->getFd();
        pfd.events = channel->getEvents();
        pfd.revents = 0;
        channels_[pfd.fd] = channel;
        pollfds_.push_back(pfd);
        channel->setIndex(pollfds_.size() - 1);
    } 
    else 
    {
        // 1. 当Channel被设置为disableAll()时会更新
        // 2. 当Channel被设置了新的events时会被更新
        assert(channels_.find(channel->getFd()) != channels_.end());
        assert(channels_[channel->getFd()] == channel);
        int idx = channel->getIndex();
        assert(0 <= idx || idx < static_cast<int>(pollfds_.size()));
        struct pollfd& pfd = pollfds_[idx];
        assert(channel->getFd() == pfd.fd || pfd.fd == -channel->getFd() - 1);
        pfd.events = channel->getEvents();
        pfd.revents = 0;
        // 当Channel被设置为disableAll()，在pollfds_标记为负数
        if (channel->isNoneEvents())
        {
            pfd.fd = -channel->getFd() - 1;
        }
    }

}


void Poller::removeChannel(Channel* channel)
{
    assertInLoopThread();
    LOG_TRACE << "fd = " << channel->getFd() << " is removed from PollPoller.";
    int idx = channel->getIndex();
    assert(channels_.find(channel->getFd()) != channels_.end());
    assert(channels_[channel->getFd()] == channel);
    channels_.erase(channel->getFd());  // 从Map中移除
    if (static_cast<int>(pollfds_.size()) - 1 == channel->getIndex())
    {
        pollfds_.pop_back();
    }
    else
    {
        int channelAtEnd = pollfds_.back().fd;
        std::iter_swap(pollfds_.begin() + idx, pollfds_.end() - 1);
        if (channelAtEnd < 0) {
            channelAtEnd = -channelAtEnd - 1;
        }
        channels_[channelAtEnd]->setIndex(idx);
        pollfds_.pop_back();
    }
    channel->setIndex(-1);
}

}   // namespace zbinbin
