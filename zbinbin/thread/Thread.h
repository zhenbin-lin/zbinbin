#ifndef __ZBINBIN_THREAD_H_
#define __ZBINBIN_THREAD_H_

#include "zbinbin/utility/noncopyable.h"
#include <functional>
#include <memory>
#include <pthread.h>
#include <functional>
#include <string>
#include <assert.h>

namespace zbinbin
{

class Thread : noncopyable
{
public:
    typedef std::function<void()> ThreadFunc;

    explicit Thread(const ThreadFunc& func, const std::string &name = "unkown thread");
    // FIXME: make it movable in C++11
    ~Thread();

    void start();
    int join(); // return pthread_join()

    bool started() const { return started_; }
    // pthread_t pthreadId() const { return pthreadId_; }
    pid_t tid() const { return tid_; }
    const std::string &name() const { return name_; }

private:

    ThreadFunc func_;
    std::string name_;
    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    pid_t tid_;

};

} // namespace zbinbin
#endif // __ZBINBIN_THREAD_H_