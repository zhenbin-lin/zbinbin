#ifndef __ZBINBIN_THREADPOOL_H_
#define __ZBINBIN_THREADPOOL_H_

#include "zbinbin/thread/Thread.h"
#include "zbinbin/thread/Mutex.h"
#include "zbinbin/thread/Condition.h"

#include <vector>
#include <queue>
#include <memory>
#include <atomic>

namespace zbinbin
{
class ThreadPool
{
public:
    using Task = std::function<void()>;

    ThreadPool(const std::string& name = "ThreadPool");
    ~ThreadPool();

    /// thread safe
    void start();
    /// thread safe
    void stop();

    /// thread safe
    void run(Task &task);

    size_t taskCount() const;

    /// MUST use before start().
    void setThreadNum(int num) { threadNum_ = num; }
private:
    void ThreadFunc();
    Task getTask();

    bool running_;

    int threadNum_;
    std::vector<std::unique_ptr<Thread>> threads_;

    std::string name_;
    Task threadInitCallback_;
    mutable MutexLock mutex_;
    std::queue<Task> tasks_;
    mutable Condition notEmpty_;
    // Condition notFull_;
};


}   // namespace zbinbin
#endif  // __ZBINBIN_THREADPOOL_H_
