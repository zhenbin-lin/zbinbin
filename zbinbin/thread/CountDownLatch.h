#ifndef __ZBINBIN_COUNTDOWNLATCH_H_
#define __ZBINBIN_COUNTDOWNLATCH_H_

#include "zbinbin/thread/Condition.h"
#include "zbinbin/thread/Mutex.h"
#include "zbinbin/utility/noncopyable.h"

namespace zbinbin
{

class CountDownLatch : noncopyable
{
public:

    explicit CountDownLatch(int count);

    void wait();

    void countDown();

    int getCount() const;

private:
    mutable MutexLock mutex_;
    Condition condition_;
    int count_;
};

}  // namespace zbinbin
#endif  // __ZBINBIN_COUNTDOWNLATCH_H_
