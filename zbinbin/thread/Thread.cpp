#include "zbinbin/thread/Thread.h"
#include <assert.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <sys/prctl.h>

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
    using ThreadFunc = sylar::Thread::ThreadFunc;
    ThreadData(const ThreadFunc& func, 
                const std::shared_ptr<pid_t> &tid,
                const std::string& name) 
                : func_(func), 
                  wptid_(tid),
                  name_(name)
    {
    }

    ThreadFunc func_;
    std::weak_ptr<pid_t> wptid_;
    std::string name_;
};

// 新线程会执行该函数
void* newthreadstart(void *obj) {
    using ThreadFunc = sylar::Thread::ThreadFunc;
    ThreadData* data = static_cast<ThreadData*>(obj);
    
    const ThreadFunc& func = data->func_;
    sylar::CurrentThread::t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid));
    assert(!data->name_.empty());
    sylar::CurrentThread::t_threadName = data->name_.c_str();
    ::prctl(PR_SET_NAME, sylar::CurrentThread::t_threadName);
    func(); // FIXME: surround with try-catch, see muduo
    // CurrentThread::t_threadName = "finished";
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
Thread::~Thread() {
    if (started_ && !joined_) {
        pthread_detach(pthreadId_);
    }
}

void Thread::start() {
    assert(!started_);
    started_ = true;
    ThreadData* data = new ThreadData(func_, ptid_, name_);
    if (pthread_create(&pthreadId_, NULL, newthreadstart, reinterpret_cast<void*>(data))) {
        started_ = false;
        delete data;
        // TODO: add log
        ::abort();
    }

}
void Thread::join() {
    assert(started_);
    assert(!joined_);
    joined_ = true;
    pthread_join(pthreadId_, NULL);
}

}   // namespace zbinzbin