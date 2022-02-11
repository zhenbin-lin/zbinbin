#include "zbinbin/log/Logging.h"
#include <iostream>

using namespace zbinbin;


int main()
{
    LOG_TRACE << "main";
    LOG_INFO << "main";
    LOG_ERROR << "main";
    LOG_DEBUG << "main";
    LOG_FATAL << "main";
}