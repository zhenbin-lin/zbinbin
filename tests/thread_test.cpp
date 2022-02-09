#include "zbinbin/thread/Thread.h"
#include <iostream>

using namespace zbinbin;

void onstart() {
    using namespace std;
    cout << "current thread [" 
    << CurrentThread::name() 
    << "] thread id: " 
    << CurrentThread::tid() 
    << std::endl;
}

int main()
{
    Thread t1(onstart, "t1");
    Thread t2(onstart, "t2");
    Thread t3(onstart, "t3");
    Thread t4(onstart, "t4");
    t1.start();
    t2.start();
    t3.start();
    t4.start();
    t3.join();
    t1.join();
    t2.join();
    t4.join();

    std::cout << "current thread [" 
    << CurrentThread::name() 
    << "] thread id: " 
    << CurrentThread::tid() 
    << std::endl;
}