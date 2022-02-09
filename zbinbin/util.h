#ifndef __SYLAR_UTIL_H_
#define __SYLAR_UTIL_H_
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <sys/prctl.h>

namespace zbinbin{

namespace {
__thread pid_t t_cachedTid = 0;

pid_t gettid() {
    return static_cast<pid_t>(::syscall(SYS_gettid));
}

}


}

#endif  // __SYLAR_UTIL_H_