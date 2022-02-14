#ifndef __ZBINBIN_EVENTLOOPTHREAD_H_
#define __ZBINBIN_EVENTLOOPTHREAD_H_

#include "zbinbin/thread/Thread.h"
#include "zbinbin/thread/Mutex.h"
#include "zbinbin/thread/Condition.h"
#include "zbinbin/utility/noncopyable.h"


#include <string>
#include <functional>

namespace zbinbin
{
class EventLoop;

class EventLoopThread : noncopyable
{
public:
    using ThreadInitCallback = std::function<void (EventLoop*)>;

    EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(), 
                    const std::string& name = std::string());
    ~EventLoopThread();

    EventLoop* startLoop();

    const std::string getThreadName() const { return thread_.name(); }

private:

    void threadFunc();

    EventLoop* loop_;
    Thread thread_;
    MutexLock mutex_;
    Condition cond_;
    ThreadInitCallback initCallback_;
};



} // namespace zbinbin
#endif  // __ZBINBIN_EVENTLOOPTHREAD_H_