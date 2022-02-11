#include "zbinbin/net/Poller.h"
#include "zbinbin/log/Logging.h"


namespace zbinbin{



void Poller::poll()
{
   int numEvents = ::poll(pollfds_.data(), NULL);
   int savedError = errno;

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
            LOG_SYSERR << "PollPoller::poll()";
        }
    }

}



}
