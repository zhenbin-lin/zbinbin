#ifndef __ZBINBIN_THREAD_H_
#define __ZBINBIN_THREAD_H_

#include "zbinbin/utility/noncopyable.h"
#include <functional>
#include <memory>
#include <pthread.h>
#include <string>
#include <assert.h>

namespace zbinbin
{

class MutexLock : noncopyable
{
public:
    MutexLock()
    : holder_(0)
    {
        pthread_mutex_init(&mutex_, NULL);
    }

    ~MutexLock()
    {
        assert(holder_ == 0);
        pthread_mutex_destroy(&mutex_);
    }

    // must be called when locked, i.e. for assertion
    bool isLockedByThisThread() const {
        return holder_ == CurrentThread::tid();
    }

    void assertLocked() {
        assert(isLockedByThisThread());
    }

  // internal usage

    void lock() {
        pthread_mutex_lock(&mutex_);
        assignHolder();
    }

    void unlock() {
        unassignHolder();
        pthread_mutex_unlock(&mutex_);
    }

    pthread_mutex_t* getPthreadMutex() /* non-const */ {
        return &mutex_;
    }

private:
    friend class Condition;

    class UnassignGuard : noncopyable
    {
    public:
        explicit UnassignGuard(MutexLock& mutex)
            : mutex_(mutex)
        {
            mutex_.unassignHolder();
        }
        ~UnassignGuard() { mutex_.assignHolder(); }
    private:
        MutexLock& mutex_;
    };

    void unassignHolder() { holder_ = 0; }

    void assignHolder() { holder_ = CurrentThread::tid(); }

    pthread_mutex_t mutex_;
    pid_t holder_;
};

class MutexLockGuard : noncopyable
{
public:
    explicit MutexLockGuard(MutexLock& mutex)
    : mutex_(mutex) {
        mutex_.lock();
    }

    ~MutexLockGuard() { mutex_.unlock(); }
private:
    MutexLock& mutex_;
};



class Thread : noncopyable
{
public:
    typedef std::function<void()> ThreadFunc;

    explicit Thread(ThreadFunc, const string &name = string());
    // FIXME: make it movable in C++11
    ~Thread();

    void start();
    int join(); // return pthread_join()

    bool started() const { return started_; }
    // pthread_t pthreadId() const { return pthreadId_; }
    pid_t tid() const { return tid_; }
    const string &name() const { return name_; }

    static int numCreated() { return numCreated_.get(); }

private:
    void setDefaultName();

    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    pid_t tid_;
    ThreadFunc func_;
    std::string name_;
};

} // namespace zbinbin
#endif // __ZBINBIN_THREAD_H_