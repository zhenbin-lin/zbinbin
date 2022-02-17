#ifndef __ZBINBIN_EVENTLOOPTHREADPOOL_H_
#define __ZBINBIN_EVENTLOOPTHREADPOOL_H_


#include "zbinbin/utility/noncopyable.h"

#include <memory>
#include <vector>
#include <string>
#include <functional>

namespace zbinbin
{
class EventLoop;
class EventLoopThread;

class EventLoopThreadPool : noncopyable
{
public:
    typedef std::function<void(EventLoop*)> ThreadInitCallback;

    EventLoopThreadPool(EventLoop* baseLoop,
                        const std::string& name = std::string());
    ~EventLoopThreadPool();

    /// Not thread safe
    /// start all Threads
    void start(const ThreadInitCallback& cb = ThreadInitCallback());

    /// Not thread safe
    /// Set the number of threads for handling input.
    /// Must be called before @c start
    void setThreadNum(int numThreads);

    /// Not thread safe
    /// valid after calling start()
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