#include <iostream>
#include <time.h>
#include "zbinbin/log/Logging.h"
#include "zbinbin/thread/Thread.h"

int main(int argc, char** argv) {
	using namespace zbinbin;
	using namespace std;
        // %m -- 消息体
        // %p -- level
        // %r -- 启动后的时间
        // %c -- 日志名称
        // %t -- thread id
        // %n -- 回车换行
        // %d -- 系统时间
        // %f -- 文件名
        // %l -- 行号
        // %F -- 函数名
    LOG_INFO << "Hello zbinbin " << 4342;
    LOG_WARN << "Hello zbinbin " << 4342;
    LOG_ERROR << "Hello zbinbin " << 4342;
	return 0;
}
