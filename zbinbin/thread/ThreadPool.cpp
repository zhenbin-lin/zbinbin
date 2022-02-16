#include "zbinbin/thread/ThreadPool.h"
#include "zbinbin/log/Logging.h"

#include <assert.h>

using namespace zbinbin;

ThreadPool::ThreadPool(const std::string& name)
    : running_(false)
    , threadNum_(0)
    , name_(name)
    , mutex_()
    , threads_()
    , tasks_()
    , notEmpty_(mutex_)
{
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::start()
{

    {
    MutexLockGuard lock(mutex_);
    if (!running_)
    {
        running_ = true;
    }
    else
    {
        LOG_FATAL << "ThreadPool::stop() be called repeat times";
        return;
    }
    }

    for (int i = 0; i < threadNum_; ++i) 
    {
        threads_.emplace_back(
            new Thread(std::bind(ThreadPool::ThreadFunc, this), name_ + "-" + std::to_string(i + 1)));
        threads_[i]->start();
    }
}


void ThreadPool::stop()
{
    {
    MutexLockGuard lock(mutex_);
    if (running_)
    {
        running_ = false;
        notEmpty_.notifyAll();
    }
    else
    {
        LOG_FATAL << "ThreadPool::stop() be called repeat times";
        return;
    }
    }

    for (auto& thr : threads_)
    {
        thr->join();
    }
}

size_t ThreadPool::taskCount() const
{
    MutexLockGuard lock(mutex_);
    return tasks_.size();
}

void ThreadPool::run(Task &task)
{
    if (threads_.empty())
    {
        task();
    }
    else
    {
        MutexLockGuard lock(mutex_);
        if (!running_)
        {
            LOG_ERROR << "ThreadPool::run() run a task, but this ThreadPool hadn't start() before.";
            return;
        }
        tasks_.push(std::move(task));
        if (tasks_.size() == 1)
        {
            notEmpty_.notify();
        }
    }
}

ThreadPool::Task ThreadPool::getTask()
{
    MutexLockGuard lock(mutex_);
    while (running_ && tasks_.empty())
    {
        notEmpty_.wait();
    }
    Task task = tasks_.front();
    tasks_.pop();
    return task;
}


void ThreadPool::ThreadFunc()
{
    try
    {
        if (threadInitCallback_)
        {
            threadInitCallback_();
        }
        while (running_)
        {
            Task task(std::move(getTask()));
            if (task)
            {
                task();
            }
        }
    }
    catch (const std::exception& ex)
    {
        fprintf(stderr, "exception caught in ThreadPool %s\n", name_.c_str());
        fprintf(stderr, "reason: %s\n", ex.what());
        abort();
    }
    catch (...)
    {
        fprintf(stderr, "unknown exception caught in ThreadPool %s\n", name_.c_str());
        throw; // rethrow
    }
}