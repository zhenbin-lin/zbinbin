#include "zbinbin/thread/CurrentThread.h"

namespace zbinbin
{
namespace CurrentThread 
{


__thread pid_t t_cachedTid = 0;                 // 当前线程的thread id
__thread char t_tidString[32];
__thread int t_tidStringLength = 6;
__thread const char* t_threadName = "unkown";    // 当前线程的名字


}   // namespace CurrentThread
}   // namespace zbinbin