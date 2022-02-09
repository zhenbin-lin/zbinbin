#ifndef __ZBINBIN_CONDITION_H_
#define __ZBINBIN_CONDITION_H_

#include "zbinbin/thread/Mutex.h"
#include "zbinbin/thread/Thread.h"
#include <pthread.h>


namespace zbinbin
{

class Condition : noncopyable
{
public:
    explicit Condition(MutexLock &mutex);
    ~Condition();

    void wait()
    {
        MutexLock::UnassignGuard ug(mutex_);
        pthread_cond_wait(&pcond_, mutex_.getPthreadMutex());
    }

    // returns true if time out, false otherwise.
    bool waitForSeconds(double seconds);

    void notify()
    {
        pthread_cond_signal(&pcond_);
    }

    void notifyAll()
    {
        pthread_cond_broadcast(&pcond_);
    }

private:
    MutexLock &mutex_;
    pthread_cond_t pcond_;
};

} // namespace zbinbin

#endif // __ZBINBIN_CONDITION_H_

