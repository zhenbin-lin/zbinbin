#ifndef __ZBINBIN_ASYNCLOGGING_H_
#define __ZBINBIN_ASYNCLOGGING_H_

#include "zbinbin/log/FixedBuffer.h"
#include "zbinbin/log/LogStream.h"
#include "zbinbin/thread/Thread.h"
#include "zbinbin/thread/Mutex.h"
#include "zbinbin/thread/Condition.h"
#include "zbinbin/thread/CountDownLatch.h"

#include <vector>
#include <string>
#include <atomic>

namespace zbinbin 
{

class AsyncLogging
{
public:
    AsyncLogging(const std::string& basename, off_t rollSize, int flushInterval = 3);
    ~AsyncLogging()
    {
        if (running_)
        {
            stop();
        }
    }

    void append(const char* logline, size_t len);

    void start()
    {
        running_ = true;
        thread_.start();
        latch_.wait();
    }

    void stop()
    {
        running_ = false;
        cond_.notify();
        thread_.join();
    }


private:

    void threadFunc();

    typedef zbinbin::FixedBuffer<kLargeBuffer> Buffer;
    typedef std::vector<std::unique_ptr<Buffer>> BufferVector;
    typedef BufferVector::value_type BufferPtr;

    const int flushInterval_;
    std::atomic<bool> running_;
    const std::string basename_;    // 写入的文件名
    const off_t rollSize_;

    zbinbin::Thread thread_;
    zbinbin::CountDownLatch latch_; // 确保之前的任务已经完成
    zbinbin::MutexLock mutex_;
    zbinbin::Condition cond_;
    BufferPtr currentBuffer_;       // 当前正在操作的缓冲区
    BufferPtr nextBuffer_;          
    BufferVector fullBuffers_;      // 已经写满的缓冲区
};




}


#endif	// __ZBINBIN_ASYNCLOGGING_H_
