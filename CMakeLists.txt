cmake_minimum_required(VERSION 2.8)
project(zbinbin)

# 详细显示make的信息
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置编译参数
set(CMAKE_CXX_FLAGS 
	"$ENV{CXXFLAGS} -rdynamic -O1 -g -std=c++14 -Wall -Wno-deprecated -Werror -Wno-unused-function -pthread")

include_directories(.)

# 设置编译的源码
set(LIB_SRC
    zbinbin/utility/Timestamp.cpp
    zbinbin/log/LogStream.cpp
    zbinbin/log/Logging.cpp
    zbinbin/log/AsyncLogging.cpp
	zbinbin/thread/Thread.cpp
	zbinbin/thread/Condition.cpp
	zbinbin/thread/CurrentThread.cpp
    zbinbin/thread/CountDownLatch.cpp
    zbinbin/net/InetAddress.cpp
    zbinbin/net/SocketOps.cpp
    zbinbin/net/Socket.cpp
    zbinbin/net/Buffer.cpp
    zbinbin/net/Channel.cpp
    zbinbin/net/Poller.cpp
    zbinbin/net/EventLoop.cpp
    zbinbin/net/Acceptor.cpp
    zbinbin/net/TcpConnection.cpp
    zbinbin/net/EventLoopThread.cpp
    zbinbin/net/EventLoopThreadPool.cpp
    zbinbin/net/TcpServer.cpp
	)

# 添加一个lib的share库，生成so文件
add_library(zbinbin SHARED ${LIB_SRC})
# add_library(zbinbin_static STATIC ${LIB_SRC})
# SET_TARGET_PROPERTIES (zbinbin_static PROERTIES OUTPUT_NAME "zbinbin")

# 生成一个测试文件
# add_executable(test tests/test.cpp)
# add_executable(thread_test tests/thread.cpp)
add_executable(log_test tests/log_test.cpp)
add_executable(AsyncLogging_test tests/AsyncLogging_test.cpp)
add_executable(Buffer_test tests/Buffer_test.cpp)
add_executable(EventLoop_test tests/EventLoop_test.cpp)
add_executable(TcpServer_test tests/TcpServer_test.cpp)
# 测试文件依赖于zbinbin
# add_dependencies(test zbinbin)
# add_dependencies(thread_test zbinbin)
add_dependencies(log_test zbinbin)
add_dependencies(AsyncLogging_test zbinbin)
add_dependencies(Buffer_test zbinbin)
add_dependencies(EventLoop_test zbinbin)
add_dependencies(TcpServer_test zbinbin)

# target_link_libraries(test zbinbin)
# target_link_libraries(thread_test zbinbin)
target_link_libraries(log_test zbinbin)
target_link_libraries(AsyncLogging_test zbinbin)
target_link_libraries(Buffer_test zbinbin)
target_link_libraries(EventLoop_test zbinbin)
target_link_libraries(TcpServer_test zbinbin)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
