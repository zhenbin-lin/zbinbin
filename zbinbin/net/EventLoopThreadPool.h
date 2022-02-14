#ifndef __ZBINBIN_EVENTLOOPTHREADPOOL_H_
#define __ZBINBIN_EVENTLOOPTHREADPOOL_H_


#include "zbinbin/utility/noncopyable.h"

#include <memory>
#include <vector>
#include <string>

namespace zbinbin
{
class EventLoop;
class EventLoopThread

class EventLoopThreadPool : noncopyable
{
public:
    typedef std::function<void(EventLoop*)> ThreadInitCallback;

    EventLoopThreadPool(EventLoop* baseLoop,
                        size_t numThreads = 0, 
                        const std::string& name = std::string());
    ~EventLoopThreadPool();

    /// start all Threads
    void start(const ThreadInitCallback& cb = ThreadInitCallback());

    // void setThreadNum(int numThreads);
    // valid after calling start()
    /// round-robin
    EventLoop* getNextLoop();

private:
    using ThreadList = std::vector<std::unique_ptr<EventLoopThread> >;
    using EventList = std::vector<EventLoop*>;

    bool started_;
    EventLoop *baseLoop_;
    const std::string& name_;
    int numThreads_;
    int nextLoop_;
    ThreadList threads_;
    EventList ioLoops_;
};


}



#endif  // __ZBINBIN_EVENTLOOPTHREADPOOL_H_