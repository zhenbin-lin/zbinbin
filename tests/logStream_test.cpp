#include "zbinbin/thread/Thread.h"
#include "zbinbin/log/LogStream.h"
#include <iostream>

using namespace zbinbin;


int main()
{
    LogStream lout(new LogStream::Buffer());
    lout << "HHH LLL SSS " << 3424 << "sdfsdf";
    std::cout << lout.release()->toString();
}