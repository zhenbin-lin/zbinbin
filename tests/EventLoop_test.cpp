#include <iostream>
#include <cstring>
#include <time.h>
#include <sys/timerfd.h>
#include "zbinbin/net/EventLoop.h"
#include "zbinbin/net/Channel.h"
#include "zbinbin/thread/Thread.h"
#include "zbinbin/log/Logging.h"



using namespace zbinbin;

EventLoop *g_loop;
int cnt = 0;

void timeout()
{
  printf("Timeout!\n");
  g_loop->quit();
}

int main()
{
    EventLoop loop;
    g_loop = &loop;

    int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    Channel channel(&loop, timerfd);
    channel.setReadCallback(timeout);
    channel.enableReading();

    struct itimerspec howlong;
    bzero(&howlong, sizeof howlong);
    howlong.it_value.tv_sec = 5;
    ::timerfd_settime(timerfd, 0, &howlong, NULL);

    loop.loop();

    // close(timerfd);
}

