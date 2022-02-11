#ifndef __ZBINBIN_MUTEX_H_
#define __ZBINBIN_MUTEX_H_
#include "zbinbin/utility/noncopyable.h"
#include "zbinbin/thread/Thread.h"
#include "zbinbin/thread/CurrentThread.h"
#include <pthread.h>
#include <assert.h>


namespace zbinbin
{

class MutexLock : noncopyable
{
public:
    MutexLock() : holder_(0) {
        pthread_mutex_init(&mutex_, NULL);
    }

    ~MutexLock() {
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
            : mutex_(mutex) {
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

} // namespace zbinbin
#endif // __ZBINBIN_MUTEX_H_