#include "zbinbin/thread/Thread.h"
#include "zbinbin/thread/CurrentThread.h"


#include <assert.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <sys/prctl.h>
#include <type_traits>


namespace zbinbin 
{


// 隐藏名称空间
namespace {

struct ThreadData;

struct ThreadData {
    ThreadData(const zbinbin::Thread::ThreadFunc& func, 
                pid_t* tid,
                const std::string& name) 
                : tid_(tid)
                , func_(func)
                , name_(name)
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
    
    pid_t* tid_;
    const zbinbin::Thread::ThreadFunc& func_;
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
    : started_(false)
    , joined_(false)
    , func_(func)
    , name_(name)
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


///
/// CurrentThread
///
namespace CurrentThread 
{
void cacheTid()
{
    if (t_cachedTid == 0)
    {
        t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid));
        t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
    }
}

bool isMainThread()
{
    return tid() == ::getpid();
}

}   // CurrentThread



}   // namespace zbinzbin