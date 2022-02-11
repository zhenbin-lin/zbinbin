#ifndef __ZBINBIN_THREAD_H_
#define __ZBINBIN_THREAD_H_

#include "zbinbin/utility/noncopyable.h"

#include <functional>
#include <pthread.h>
#include <string>


namespace zbinbin
{

/// 默认情况下Thread的析构函数会自动回收线程资源
/// 可以调用join()，将资源交由main Thread回收
class Thread : noncopyable
{
public:
    typedef std::function<void()> ThreadFunc;

    explicit Thread(const ThreadFunc& func, const std::string &name = std::string());
    // FIXME: make it movable in C++11
    ~Thread();

    void start();

    // 设置子线程为join，main thread会等待子线程终止
    int join();

    bool started() const { return started_; }
    pid_t tid() const { return tid_; }
    const std::string &name() const { return name_; }

private:

    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    pid_t tid_;
    ThreadFunc func_;
    std::string name_;
};

} // namespace zbinbin
#endif // __ZBINBIN_THREAD_H_