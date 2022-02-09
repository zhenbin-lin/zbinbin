#include "zbinbin/thread/Thread.h"
#include <assert.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <sys/prctl.h>
#include <type_traits>


namespace zbinbin {

namespace CurrentThread {

// 当前线程的thread id
__thread pid_t t_cachedTid = 0; 
// 当前线程的名字
__thread const char* t_threadName = nullptr;

pid_t tid() {
    if (t_cachedTid == 0) {
        // main thread
        t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid));
    }
    return t_cachedTid;
}

const std::string name() {
    if (t_threadName == nullptr) {
        // main thread
        t_threadName = "main";
    } 
    return std::string(t_threadName);
}

}   // CurrentThread



// 隐藏名称空间
namespace {

struct ThreadData;

struct ThreadData {
    ThreadData(const zbinbin::Thread::ThreadFunc& func, 
                pid_t* tid,
                const std::string& name) 
                : func_(func), 
                  tid_(tid),
                  name_(name)
    {
    }

    void runInNewThread()
    {
        // 用于填回主线程中的Thread::tid_
        *tid_ = zbinbin::CurrentThread::tid();
        assert(!name_.empty());
        zbinbin::CurrentThread::t_threadName = name_.c_str();
        ::prctl(PR_SET_NAME, zbinbin::CurrentThread::t_threadName);
        // TODO 输出到日志中
        try
        {
            func_();
            zbinbin::CurrentThread::t_threadName = "finished";
        }
        catch (const std::exception& ex)
        {
            zbinbin::CurrentThread::t_threadName = "crashed";
            fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
            fprintf(stderr, "reason: %s\n", ex.what());
            abort();
        }
        catch (...)
        {
            zbinbin::CurrentThread::t_threadName = "crashed";
            fprintf(stderr, "unknown exception caught in Thread %s\n", name_.c_str());
            throw; // rethrow
        }
    }

    /// data
    const zbinbin::Thread::ThreadFunc& func_;
    pid_t* tid_;
    std::string name_;

};

// 新线程会执行该函数
void* newthreadstart(void *obj) {
    ThreadData* data = static_cast<ThreadData*>(obj);
    data->runInNewThread();
    delete data;
    return NULL;
}


}   // 隐藏名称空间



Thread::Thread(const ThreadFunc& func, const std::string& name) 
    : func_(func)
    , name_(name)
    , started_(false)
    , joined_(false)
{
    
}
Thread::~Thread() 
{
    if (started_ && !joined_) {
        pthread_detach(pthreadId_);
    }
}

void Thread::start() 
{
    assert(!started_);
    started_ = true;
    ThreadData* data = new ThreadData(func_, &tid_, name_);
    if (pthread_create(&pthreadId_, NULL, newthreadstart, reinterpret_cast<void*>(data))) {
        started_ = false;
        delete data;
        // TODO: add log
        ::abort();
    }
}

int Thread::join() {
    assert(started_);
    assert(!joined_);
    joined_ = true;
    return pthread_join(pthreadId_, NULL);
}

}   // namespace zbinzbin