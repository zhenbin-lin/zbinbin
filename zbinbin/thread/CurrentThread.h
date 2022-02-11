#ifndef __ZBINBIN_CURRENTTHREAD_H_
#define __ZBINBIN_CURRENTTHREAD_H_

#include <pthread.h>
#include <string>

namespace zbinbin
{

namespace CurrentThread {


extern __thread pid_t t_cachedTid;          // 当前线程的thread id
extern __thread char t_tidString[32];       // tid的string格式
extern __thread int t_tidStringLength;      // tid的string.length
extern __thread const char* t_threadName;   // 当前线程的名字


void cacheTid();

/// 
/// 获取线程的内核线程号
/// 
inline pid_t tid()
{
    if (t_cachedTid == 0)
    {
        cacheTid();
    }
    return t_cachedTid;
}


inline const char* tidString()
{
    return t_tidString;
}

inline size_t tidStringLength()
{
    return t_tidStringLength;
}

/// 
/// 获取线程名字
/// 
inline const char* name()
{
    return t_threadName;
}

inline bool inMainThread();

}   // CurrentThread

} // namespace zbinbin
#endif // __ZBINBIN_CURRENTTHREAD_H_