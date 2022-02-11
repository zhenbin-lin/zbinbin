#include "zbinbin/log/AsyncLogging.h"
#include "zbinbin/utility/Timestamp.h"
#include <functional>
#include <fstream>
#include <iostream> // for DEBUG

namespace zbinbin
{
AsyncLogging::AsyncLogging(const std::string& basename, off_t rollSize, int flushInterval)
    : flushInterval_(flushInterval)
    , running_(false)
    , basename_(basename)
    , rollSize_(rollSize)
    , thread_(std::bind(&AsyncLogging::threadFunc, this), "Logging")
    , latch_(1)
    , mutex_()
    , cond_(mutex_)
    , currentBuffer_(new Buffer)
    , nextBuffer_(new Buffer)
    , fullBuffers_()
{
    currentBuffer_->bzero();
    nextBuffer_->bzero();
    fullBuffers_.reserve(16);
}

void AsyncLogging::append(const char* logline, size_t len)
{
    zbinbin::MutexLockGuard lock(mutex_);
    if (currentBuffer_->avail() > len)
    {
        currentBuffer_->append(logline, len);
    } 
    else
    {
        fullBuffers_.push_back(std::move(currentBuffer_));

        if (nextBuffer_)
        {
            currentBuffer_ = std::move(nextBuffer_);
        } 
        else 
        {
            currentBuffer_.reset(new Buffer); // Rarely happens
        }
        currentBuffer_->append(logline, len);
        cond_.notify(); // 通知后台线程可以读数据
    }
}

void AsyncLogging::threadFunc()
{
    assert(running_ == true);
    latch_.countDown();     // 前后端进行同步，前端start()时会block在latch_上，等待后端线程开始后才能解锁。 有必要？？
    std::ofstream output;
    output.open(basename_);

    BufferPtr newBuffer1(new Buffer);
    BufferPtr newBuffer2(new Buffer);

    newBuffer1->bzero();
    newBuffer2->bzero();

    BufferVector buffersToWrite;
    buffersToWrite.reserve(16);

    while (running_)
    {
        assert(newBuffer1 && newBuffer1->length() == 0);
        assert(newBuffer2 && newBuffer2->length() == 0);    
        assert(buffersToWrite.empty());
        {
            zbinbin::MutexLockGuard lock(mutex_);
            if (fullBuffers_.empty())
            {
                cond_.waitForSeconds(flushInterval_);   // 每flushInterval_秒就刷新一次缓冲区
            }
            fullBuffers_.push_back(std::move(currentBuffer_));
            currentBuffer_ = std::move(newBuffer1);
            buffersToWrite.swap(fullBuffers_);
            if (!nextBuffer_)
            {
                nextBuffer_ = std::move(newBuffer2);
            }
        }    
        assert(!buffersToWrite.empty());

        // 日志过载设计
        if (buffersToWrite.size() > 25)
        {
            char buf[256];
            snprintf(buf, sizeof buf, "Dropped log messages at %s, %zd larger buffers\n",
                    Timestamp::now().toFormattedString().c_str(),
                    buffersToWrite.size() - 2);
            fputs(buf, stderr);
            output << buf;  // file stream
            buffersToWrite.erase(buffersToWrite.begin() + 2, buffersToWrite.end());
        }
        for (const auto& buffer : buffersToWrite)
        {
            output << buffer->data() << ':' << "sss";
        }
        if (!newBuffer1)
        {
            assert(!buffersToWrite.empty());
            newBuffer1 = std::move(buffersToWrite.back());
            buffersToWrite.pop_back();
            newBuffer1->reset();
        }

        if (!newBuffer2)
        {
            assert(!buffersToWrite.empty());
            newBuffer2 = std::move(buffersToWrite.back());
            buffersToWrite.pop_back();
            newBuffer2->reset();            
        }
        buffersToWrite.clear();
        output.flush();
    }
    output.flush();
}

}   // namespace zbinbin
