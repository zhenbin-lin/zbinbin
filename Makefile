# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/binwatson/share/zbinbin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/binwatson/share/zbinbin

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/binwatson/share/zbinbin/CMakeFiles /home/binwatson/share/zbinbin/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/binwatson/share/zbinbin/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named log_test

# Build rule for target.
log_test: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 log_test
.PHONY : log_test

# fast build rule for target.
log_test/fast:
	$(MAKE) -f CMakeFiles/log_test.dir/build.make CMakeFiles/log_test.dir/build
.PHONY : log_test/fast

#=============================================================================
# Target rules for targets named zbinbin

# Build rule for target.
zbinbin: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 zbinbin
.PHONY : zbinbin

# fast build rule for target.
zbinbin/fast:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/build
.PHONY : zbinbin/fast

#=============================================================================
# Target rules for targets named AsyncLogging_test

# Build rule for target.
AsyncLogging_test: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 AsyncLogging_test
.PHONY : AsyncLogging_test

# fast build rule for target.
AsyncLogging_test/fast:
	$(MAKE) -f CMakeFiles/AsyncLogging_test.dir/build.make CMakeFiles/AsyncLogging_test.dir/build
.PHONY : AsyncLogging_test/fast

#=============================================================================
# Target rules for targets named Buffer_test

# Build rule for target.
Buffer_test: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Buffer_test
.PHONY : Buffer_test

# fast build rule for target.
Buffer_test/fast:
	$(MAKE) -f CMakeFiles/Buffer_test.dir/build.make CMakeFiles/Buffer_test.dir/build
.PHONY : Buffer_test/fast

#=============================================================================
# Target rules for targets named EventLoop_test

# Build rule for target.
EventLoop_test: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 EventLoop_test
.PHONY : EventLoop_test

# fast build rule for target.
EventLoop_test/fast:
	$(MAKE) -f CMakeFiles/EventLoop_test.dir/build.make CMakeFiles/EventLoop_test.dir/build
.PHONY : EventLoop_test/fast

#=============================================================================
# Target rules for targets named TcpServer_test

# Build rule for target.
TcpServer_test: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 TcpServer_test
.PHONY : TcpServer_test

# fast build rule for target.
TcpServer_test/fast:
	$(MAKE) -f CMakeFiles/TcpServer_test.dir/build.make CMakeFiles/TcpServer_test.dir/build
.PHONY : TcpServer_test/fast

tests/AsyncLogging_test.o: tests/AsyncLogging_test.cpp.o

.PHONY : tests/AsyncLogging_test.o

# target to build an object file
tests/AsyncLogging_test.cpp.o:
	$(MAKE) -f CMakeFiles/AsyncLogging_test.dir/build.make CMakeFiles/AsyncLogging_test.dir/tests/AsyncLogging_test.cpp.o
.PHONY : tests/AsyncLogging_test.cpp.o

tests/AsyncLogging_test.i: tests/AsyncLogging_test.cpp.i

.PHONY : tests/AsyncLogging_test.i

# target to preprocess a source file
tests/AsyncLogging_test.cpp.i:
	$(MAKE) -f CMakeFiles/AsyncLogging_test.dir/build.make CMakeFiles/AsyncLogging_test.dir/tests/AsyncLogging_test.cpp.i
.PHONY : tests/AsyncLogging_test.cpp.i

tests/AsyncLogging_test.s: tests/AsyncLogging_test.cpp.s

.PHONY : tests/AsyncLogging_test.s

# target to generate assembly for a file
tests/AsyncLogging_test.cpp.s:
	$(MAKE) -f CMakeFiles/AsyncLogging_test.dir/build.make CMakeFiles/AsyncLogging_test.dir/tests/AsyncLogging_test.cpp.s
.PHONY : tests/AsyncLogging_test.cpp.s

tests/Buffer_test.o: tests/Buffer_test.cpp.o

.PHONY : tests/Buffer_test.o

# target to build an object file
tests/Buffer_test.cpp.o:
	$(MAKE) -f CMakeFiles/Buffer_test.dir/build.make CMakeFiles/Buffer_test.dir/tests/Buffer_test.cpp.o
.PHONY : tests/Buffer_test.cpp.o

tests/Buffer_test.i: tests/Buffer_test.cpp.i

.PHONY : tests/Buffer_test.i

# target to preprocess a source file
tests/Buffer_test.cpp.i:
	$(MAKE) -f CMakeFiles/Buffer_test.dir/build.make CMakeFiles/Buffer_test.dir/tests/Buffer_test.cpp.i
.PHONY : tests/Buffer_test.cpp.i

tests/Buffer_test.s: tests/Buffer_test.cpp.s

.PHONY : tests/Buffer_test.s

# target to generate assembly for a file
tests/Buffer_test.cpp.s:
	$(MAKE) -f CMakeFiles/Buffer_test.dir/build.make CMakeFiles/Buffer_test.dir/tests/Buffer_test.cpp.s
.PHONY : tests/Buffer_test.cpp.s

tests/EventLoop_test.o: tests/EventLoop_test.cpp.o

.PHONY : tests/EventLoop_test.o

# target to build an object file
tests/EventLoop_test.cpp.o:
	$(MAKE) -f CMakeFiles/EventLoop_test.dir/build.make CMakeFiles/EventLoop_test.dir/tests/EventLoop_test.cpp.o
.PHONY : tests/EventLoop_test.cpp.o

tests/EventLoop_test.i: tests/EventLoop_test.cpp.i

.PHONY : tests/EventLoop_test.i

# target to preprocess a source file
tests/EventLoop_test.cpp.i:
	$(MAKE) -f CMakeFiles/EventLoop_test.dir/build.make CMakeFiles/EventLoop_test.dir/tests/EventLoop_test.cpp.i
.PHONY : tests/EventLoop_test.cpp.i

tests/EventLoop_test.s: tests/EventLoop_test.cpp.s

.PHONY : tests/EventLoop_test.s

# target to generate assembly for a file
tests/EventLoop_test.cpp.s:
	$(MAKE) -f CMakeFiles/EventLoop_test.dir/build.make CMakeFiles/EventLoop_test.dir/tests/EventLoop_test.cpp.s
.PHONY : tests/EventLoop_test.cpp.s

tests/TcpServer_test.o: tests/TcpServer_test.cpp.o

.PHONY : tests/TcpServer_test.o

# target to build an object file
tests/TcpServer_test.cpp.o:
	$(MAKE) -f CMakeFiles/TcpServer_test.dir/build.make CMakeFiles/TcpServer_test.dir/tests/TcpServer_test.cpp.o
.PHONY : tests/TcpServer_test.cpp.o

tests/TcpServer_test.i: tests/TcpServer_test.cpp.i

.PHONY : tests/TcpServer_test.i

# target to preprocess a source file
tests/TcpServer_test.cpp.i:
	$(MAKE) -f CMakeFiles/TcpServer_test.dir/build.make CMakeFiles/TcpServer_test.dir/tests/TcpServer_test.cpp.i
.PHONY : tests/TcpServer_test.cpp.i

tests/TcpServer_test.s: tests/TcpServer_test.cpp.s

.PHONY : tests/TcpServer_test.s

# target to generate assembly for a file
tests/TcpServer_test.cpp.s:
	$(MAKE) -f CMakeFiles/TcpServer_test.dir/build.make CMakeFiles/TcpServer_test.dir/tests/TcpServer_test.cpp.s
.PHONY : tests/TcpServer_test.cpp.s

tests/log_test.o: tests/log_test.cpp.o

.PHONY : tests/log_test.o

# target to build an object file
tests/log_test.cpp.o:
	$(MAKE) -f CMakeFiles/log_test.dir/build.make CMakeFiles/log_test.dir/tests/log_test.cpp.o
.PHONY : tests/log_test.cpp.o

tests/log_test.i: tests/log_test.cpp.i

.PHONY : tests/log_test.i

# target to preprocess a source file
tests/log_test.cpp.i:
	$(MAKE) -f CMakeFiles/log_test.dir/build.make CMakeFiles/log_test.dir/tests/log_test.cpp.i
.PHONY : tests/log_test.cpp.i

tests/log_test.s: tests/log_test.cpp.s

.PHONY : tests/log_test.s

# target to generate assembly for a file
tests/log_test.cpp.s:
	$(MAKE) -f CMakeFiles/log_test.dir/build.make CMakeFiles/log_test.dir/tests/log_test.cpp.s
.PHONY : tests/log_test.cpp.s

zbinbin/log/AsyncLogging.o: zbinbin/log/AsyncLogging.cpp.o

.PHONY : zbinbin/log/AsyncLogging.o

# target to build an object file
zbinbin/log/AsyncLogging.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/log/AsyncLogging.cpp.o
.PHONY : zbinbin/log/AsyncLogging.cpp.o

zbinbin/log/AsyncLogging.i: zbinbin/log/AsyncLogging.cpp.i

.PHONY : zbinbin/log/AsyncLogging.i

# target to preprocess a source file
zbinbin/log/AsyncLogging.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/log/AsyncLogging.cpp.i
.PHONY : zbinbin/log/AsyncLogging.cpp.i

zbinbin/log/AsyncLogging.s: zbinbin/log/AsyncLogging.cpp.s

.PHONY : zbinbin/log/AsyncLogging.s

# target to generate assembly for a file
zbinbin/log/AsyncLogging.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/log/AsyncLogging.cpp.s
.PHONY : zbinbin/log/AsyncLogging.cpp.s

zbinbin/log/LogStream.o: zbinbin/log/LogStream.cpp.o

.PHONY : zbinbin/log/LogStream.o

# target to build an object file
zbinbin/log/LogStream.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o
.PHONY : zbinbin/log/LogStream.cpp.o

zbinbin/log/LogStream.i: zbinbin/log/LogStream.cpp.i

.PHONY : zbinbin/log/LogStream.i

# target to preprocess a source file
zbinbin/log/LogStream.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.i
.PHONY : zbinbin/log/LogStream.cpp.i

zbinbin/log/LogStream.s: zbinbin/log/LogStream.cpp.s

.PHONY : zbinbin/log/LogStream.s

# target to generate assembly for a file
zbinbin/log/LogStream.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.s
.PHONY : zbinbin/log/LogStream.cpp.s

zbinbin/log/Logging.o: zbinbin/log/Logging.cpp.o

.PHONY : zbinbin/log/Logging.o

# target to build an object file
zbinbin/log/Logging.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/log/Logging.cpp.o
.PHONY : zbinbin/log/Logging.cpp.o

zbinbin/log/Logging.i: zbinbin/log/Logging.cpp.i

.PHONY : zbinbin/log/Logging.i

# target to preprocess a source file
zbinbin/log/Logging.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/log/Logging.cpp.i
.PHONY : zbinbin/log/Logging.cpp.i

zbinbin/log/Logging.s: zbinbin/log/Logging.cpp.s

.PHONY : zbinbin/log/Logging.s

# target to generate assembly for a file
zbinbin/log/Logging.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/log/Logging.cpp.s
.PHONY : zbinbin/log/Logging.cpp.s

zbinbin/net/Acceptor.o: zbinbin/net/Acceptor.cpp.o

.PHONY : zbinbin/net/Acceptor.o

# target to build an object file
zbinbin/net/Acceptor.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Acceptor.cpp.o
.PHONY : zbinbin/net/Acceptor.cpp.o

zbinbin/net/Acceptor.i: zbinbin/net/Acceptor.cpp.i

.PHONY : zbinbin/net/Acceptor.i

# target to preprocess a source file
zbinbin/net/Acceptor.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Acceptor.cpp.i
.PHONY : zbinbin/net/Acceptor.cpp.i

zbinbin/net/Acceptor.s: zbinbin/net/Acceptor.cpp.s

.PHONY : zbinbin/net/Acceptor.s

# target to generate assembly for a file
zbinbin/net/Acceptor.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Acceptor.cpp.s
.PHONY : zbinbin/net/Acceptor.cpp.s

zbinbin/net/Buffer.o: zbinbin/net/Buffer.cpp.o

.PHONY : zbinbin/net/Buffer.o

# target to build an object file
zbinbin/net/Buffer.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Buffer.cpp.o
.PHONY : zbinbin/net/Buffer.cpp.o

zbinbin/net/Buffer.i: zbinbin/net/Buffer.cpp.i

.PHONY : zbinbin/net/Buffer.i

# target to preprocess a source file
zbinbin/net/Buffer.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Buffer.cpp.i
.PHONY : zbinbin/net/Buffer.cpp.i

zbinbin/net/Buffer.s: zbinbin/net/Buffer.cpp.s

.PHONY : zbinbin/net/Buffer.s

# target to generate assembly for a file
zbinbin/net/Buffer.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Buffer.cpp.s
.PHONY : zbinbin/net/Buffer.cpp.s

zbinbin/net/Channel.o: zbinbin/net/Channel.cpp.o

.PHONY : zbinbin/net/Channel.o

# target to build an object file
zbinbin/net/Channel.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Channel.cpp.o
.PHONY : zbinbin/net/Channel.cpp.o

zbinbin/net/Channel.i: zbinbin/net/Channel.cpp.i

.PHONY : zbinbin/net/Channel.i

# target to preprocess a source file
zbinbin/net/Channel.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Channel.cpp.i
.PHONY : zbinbin/net/Channel.cpp.i

zbinbin/net/Channel.s: zbinbin/net/Channel.cpp.s

.PHONY : zbinbin/net/Channel.s

# target to generate assembly for a file
zbinbin/net/Channel.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Channel.cpp.s
.PHONY : zbinbin/net/Channel.cpp.s

zbinbin/net/EventLoop.o: zbinbin/net/EventLoop.cpp.o

.PHONY : zbinbin/net/EventLoop.o

# target to build an object file
zbinbin/net/EventLoop.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/EventLoop.cpp.o
.PHONY : zbinbin/net/EventLoop.cpp.o

zbinbin/net/EventLoop.i: zbinbin/net/EventLoop.cpp.i

.PHONY : zbinbin/net/EventLoop.i

# target to preprocess a source file
zbinbin/net/EventLoop.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/EventLoop.cpp.i
.PHONY : zbinbin/net/EventLoop.cpp.i

zbinbin/net/EventLoop.s: zbinbin/net/EventLoop.cpp.s

.PHONY : zbinbin/net/EventLoop.s

# target to generate assembly for a file
zbinbin/net/EventLoop.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/EventLoop.cpp.s
.PHONY : zbinbin/net/EventLoop.cpp.s

zbinbin/net/EventLoopThread.o: zbinbin/net/EventLoopThread.cpp.o

.PHONY : zbinbin/net/EventLoopThread.o

# target to build an object file
zbinbin/net/EventLoopThread.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/EventLoopThread.cpp.o
.PHONY : zbinbin/net/EventLoopThread.cpp.o

zbinbin/net/EventLoopThread.i: zbinbin/net/EventLoopThread.cpp.i

.PHONY : zbinbin/net/EventLoopThread.i

# target to preprocess a source file
zbinbin/net/EventLoopThread.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/EventLoopThread.cpp.i
.PHONY : zbinbin/net/EventLoopThread.cpp.i

zbinbin/net/EventLoopThread.s: zbinbin/net/EventLoopThread.cpp.s

.PHONY : zbinbin/net/EventLoopThread.s

# target to generate assembly for a file
zbinbin/net/EventLoopThread.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/EventLoopThread.cpp.s
.PHONY : zbinbin/net/EventLoopThread.cpp.s

zbinbin/net/EventLoopThreadPool.o: zbinbin/net/EventLoopThreadPool.cpp.o

.PHONY : zbinbin/net/EventLoopThreadPool.o

# target to build an object file
zbinbin/net/EventLoopThreadPool.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/EventLoopThreadPool.cpp.o
.PHONY : zbinbin/net/EventLoopThreadPool.cpp.o

zbinbin/net/EventLoopThreadPool.i: zbinbin/net/EventLoopThreadPool.cpp.i

.PHONY : zbinbin/net/EventLoopThreadPool.i

# target to preprocess a source file
zbinbin/net/EventLoopThreadPool.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/EventLoopThreadPool.cpp.i
.PHONY : zbinbin/net/EventLoopThreadPool.cpp.i

zbinbin/net/EventLoopThreadPool.s: zbinbin/net/EventLoopThreadPool.cpp.s

.PHONY : zbinbin/net/EventLoopThreadPool.s

# target to generate assembly for a file
zbinbin/net/EventLoopThreadPool.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/EventLoopThreadPool.cpp.s
.PHONY : zbinbin/net/EventLoopThreadPool.cpp.s

zbinbin/net/InetAddress.o: zbinbin/net/InetAddress.cpp.o

.PHONY : zbinbin/net/InetAddress.o

# target to build an object file
zbinbin/net/InetAddress.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/InetAddress.cpp.o
.PHONY : zbinbin/net/InetAddress.cpp.o

zbinbin/net/InetAddress.i: zbinbin/net/InetAddress.cpp.i

.PHONY : zbinbin/net/InetAddress.i

# target to preprocess a source file
zbinbin/net/InetAddress.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/InetAddress.cpp.i
.PHONY : zbinbin/net/InetAddress.cpp.i

zbinbin/net/InetAddress.s: zbinbin/net/InetAddress.cpp.s

.PHONY : zbinbin/net/InetAddress.s

# target to generate assembly for a file
zbinbin/net/InetAddress.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/InetAddress.cpp.s
.PHONY : zbinbin/net/InetAddress.cpp.s

zbinbin/net/Poller.o: zbinbin/net/Poller.cpp.o

.PHONY : zbinbin/net/Poller.o

# target to build an object file
zbinbin/net/Poller.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Poller.cpp.o
.PHONY : zbinbin/net/Poller.cpp.o

zbinbin/net/Poller.i: zbinbin/net/Poller.cpp.i

.PHONY : zbinbin/net/Poller.i

# target to preprocess a source file
zbinbin/net/Poller.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Poller.cpp.i
.PHONY : zbinbin/net/Poller.cpp.i

zbinbin/net/Poller.s: zbinbin/net/Poller.cpp.s

.PHONY : zbinbin/net/Poller.s

# target to generate assembly for a file
zbinbin/net/Poller.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Poller.cpp.s
.PHONY : zbinbin/net/Poller.cpp.s

zbinbin/net/Socket.o: zbinbin/net/Socket.cpp.o

.PHONY : zbinbin/net/Socket.o

# target to build an object file
zbinbin/net/Socket.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Socket.cpp.o
.PHONY : zbinbin/net/Socket.cpp.o

zbinbin/net/Socket.i: zbinbin/net/Socket.cpp.i

.PHONY : zbinbin/net/Socket.i

# target to preprocess a source file
zbinbin/net/Socket.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Socket.cpp.i
.PHONY : zbinbin/net/Socket.cpp.i

zbinbin/net/Socket.s: zbinbin/net/Socket.cpp.s

.PHONY : zbinbin/net/Socket.s

# target to generate assembly for a file
zbinbin/net/Socket.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/Socket.cpp.s
.PHONY : zbinbin/net/Socket.cpp.s

zbinbin/net/SocketOps.o: zbinbin/net/SocketOps.cpp.o

.PHONY : zbinbin/net/SocketOps.o

# target to build an object file
zbinbin/net/SocketOps.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/SocketOps.cpp.o
.PHONY : zbinbin/net/SocketOps.cpp.o

zbinbin/net/SocketOps.i: zbinbin/net/SocketOps.cpp.i

.PHONY : zbinbin/net/SocketOps.i

# target to preprocess a source file
zbinbin/net/SocketOps.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/SocketOps.cpp.i
.PHONY : zbinbin/net/SocketOps.cpp.i

zbinbin/net/SocketOps.s: zbinbin/net/SocketOps.cpp.s

.PHONY : zbinbin/net/SocketOps.s

# target to generate assembly for a file
zbinbin/net/SocketOps.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/SocketOps.cpp.s
.PHONY : zbinbin/net/SocketOps.cpp.s

zbinbin/net/TcpConnection.o: zbinbin/net/TcpConnection.cpp.o

.PHONY : zbinbin/net/TcpConnection.o

# target to build an object file
zbinbin/net/TcpConnection.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/TcpConnection.cpp.o
.PHONY : zbinbin/net/TcpConnection.cpp.o

zbinbin/net/TcpConnection.i: zbinbin/net/TcpConnection.cpp.i

.PHONY : zbinbin/net/TcpConnection.i

# target to preprocess a source file
zbinbin/net/TcpConnection.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/TcpConnection.cpp.i
.PHONY : zbinbin/net/TcpConnection.cpp.i

zbinbin/net/TcpConnection.s: zbinbin/net/TcpConnection.cpp.s

.PHONY : zbinbin/net/TcpConnection.s

# target to generate assembly for a file
zbinbin/net/TcpConnection.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/TcpConnection.cpp.s
.PHONY : zbinbin/net/TcpConnection.cpp.s

zbinbin/net/TcpServer.o: zbinbin/net/TcpServer.cpp.o

.PHONY : zbinbin/net/TcpServer.o

# target to build an object file
zbinbin/net/TcpServer.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/TcpServer.cpp.o
.PHONY : zbinbin/net/TcpServer.cpp.o

zbinbin/net/TcpServer.i: zbinbin/net/TcpServer.cpp.i

.PHONY : zbinbin/net/TcpServer.i

# target to preprocess a source file
zbinbin/net/TcpServer.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/TcpServer.cpp.i
.PHONY : zbinbin/net/TcpServer.cpp.i

zbinbin/net/TcpServer.s: zbinbin/net/TcpServer.cpp.s

.PHONY : zbinbin/net/TcpServer.s

# target to generate assembly for a file
zbinbin/net/TcpServer.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/net/TcpServer.cpp.s
.PHONY : zbinbin/net/TcpServer.cpp.s

zbinbin/thread/Condition.o: zbinbin/thread/Condition.cpp.o

.PHONY : zbinbin/thread/Condition.o

# target to build an object file
zbinbin/thread/Condition.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o
.PHONY : zbinbin/thread/Condition.cpp.o

zbinbin/thread/Condition.i: zbinbin/thread/Condition.cpp.i

.PHONY : zbinbin/thread/Condition.i

# target to preprocess a source file
zbinbin/thread/Condition.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.i
.PHONY : zbinbin/thread/Condition.cpp.i

zbinbin/thread/Condition.s: zbinbin/thread/Condition.cpp.s

.PHONY : zbinbin/thread/Condition.s

# target to generate assembly for a file
zbinbin/thread/Condition.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.s
.PHONY : zbinbin/thread/Condition.cpp.s

zbinbin/thread/CountDownLatch.o: zbinbin/thread/CountDownLatch.cpp.o

.PHONY : zbinbin/thread/CountDownLatch.o

# target to build an object file
zbinbin/thread/CountDownLatch.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/thread/CountDownLatch.cpp.o
.PHONY : zbinbin/thread/CountDownLatch.cpp.o

zbinbin/thread/CountDownLatch.i: zbinbin/thread/CountDownLatch.cpp.i

.PHONY : zbinbin/thread/CountDownLatch.i

# target to preprocess a source file
zbinbin/thread/CountDownLatch.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/thread/CountDownLatch.cpp.i
.PHONY : zbinbin/thread/CountDownLatch.cpp.i

zbinbin/thread/CountDownLatch.s: zbinbin/thread/CountDownLatch.cpp.s

.PHONY : zbinbin/thread/CountDownLatch.s

# target to generate assembly for a file
zbinbin/thread/CountDownLatch.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/thread/CountDownLatch.cpp.s
.PHONY : zbinbin/thread/CountDownLatch.cpp.s

zbinbin/thread/CurrentThread.o: zbinbin/thread/CurrentThread.cpp.o

.PHONY : zbinbin/thread/CurrentThread.o

# target to build an object file
zbinbin/thread/CurrentThread.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/thread/CurrentThread.cpp.o
.PHONY : zbinbin/thread/CurrentThread.cpp.o

zbinbin/thread/CurrentThread.i: zbinbin/thread/CurrentThread.cpp.i

.PHONY : zbinbin/thread/CurrentThread.i

# target to preprocess a source file
zbinbin/thread/CurrentThread.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/thread/CurrentThread.cpp.i
.PHONY : zbinbin/thread/CurrentThread.cpp.i

zbinbin/thread/CurrentThread.s: zbinbin/thread/CurrentThread.cpp.s

.PHONY : zbinbin/thread/CurrentThread.s

# target to generate assembly for a file
zbinbin/thread/CurrentThread.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/thread/CurrentThread.cpp.s
.PHONY : zbinbin/thread/CurrentThread.cpp.s

zbinbin/thread/Thread.o: zbinbin/thread/Thread.cpp.o

.PHONY : zbinbin/thread/Thread.o

# target to build an object file
zbinbin/thread/Thread.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o
.PHONY : zbinbin/thread/Thread.cpp.o

zbinbin/thread/Thread.i: zbinbin/thread/Thread.cpp.i

.PHONY : zbinbin/thread/Thread.i

# target to preprocess a source file
zbinbin/thread/Thread.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.i
.PHONY : zbinbin/thread/Thread.cpp.i

zbinbin/thread/Thread.s: zbinbin/thread/Thread.cpp.s

.PHONY : zbinbin/thread/Thread.s

# target to generate assembly for a file
zbinbin/thread/Thread.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.s
.PHONY : zbinbin/thread/Thread.cpp.s

zbinbin/utility/Timestamp.o: zbinbin/utility/Timestamp.cpp.o

.PHONY : zbinbin/utility/Timestamp.o

# target to build an object file
zbinbin/utility/Timestamp.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/utility/Timestamp.cpp.o
.PHONY : zbinbin/utility/Timestamp.cpp.o

zbinbin/utility/Timestamp.i: zbinbin/utility/Timestamp.cpp.i

.PHONY : zbinbin/utility/Timestamp.i

# target to preprocess a source file
zbinbin/utility/Timestamp.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/utility/Timestamp.cpp.i
.PHONY : zbinbin/utility/Timestamp.cpp.i

zbinbin/utility/Timestamp.s: zbinbin/utility/Timestamp.cpp.s

.PHONY : zbinbin/utility/Timestamp.s

# target to generate assembly for a file
zbinbin/utility/Timestamp.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/utility/Timestamp.cpp.s
.PHONY : zbinbin/utility/Timestamp.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... log_test"
	@echo "... zbinbin"
	@echo "... AsyncLogging_test"
	@echo "... Buffer_test"
	@echo "... EventLoop_test"
	@echo "... edit_cache"
	@echo "... TcpServer_test"
	@echo "... tests/AsyncLogging_test.o"
	@echo "... tests/AsyncLogging_test.i"
	@echo "... tests/AsyncLogging_test.s"
	@echo "... tests/Buffer_test.o"
	@echo "... tests/Buffer_test.i"
	@echo "... tests/Buffer_test.s"
	@echo "... tests/EventLoop_test.o"
	@echo "... tests/EventLoop_test.i"
	@echo "... tests/EventLoop_test.s"
	@echo "... tests/TcpServer_test.o"
	@echo "... tests/TcpServer_test.i"
	@echo "... tests/TcpServer_test.s"
	@echo "... tests/log_test.o"
	@echo "... tests/log_test.i"
	@echo "... tests/log_test.s"
	@echo "... zbinbin/log/AsyncLogging.o"
	@echo "... zbinbin/log/AsyncLogging.i"
	@echo "... zbinbin/log/AsyncLogging.s"
	@echo "... zbinbin/log/LogStream.o"
	@echo "... zbinbin/log/LogStream.i"
	@echo "... zbinbin/log/LogStream.s"
	@echo "... zbinbin/log/Logging.o"
	@echo "... zbinbin/log/Logging.i"
	@echo "... zbinbin/log/Logging.s"
	@echo "... zbinbin/net/Acceptor.o"
	@echo "... zbinbin/net/Acceptor.i"
	@echo "... zbinbin/net/Acceptor.s"
	@echo "... zbinbin/net/Buffer.o"
	@echo "... zbinbin/net/Buffer.i"
	@echo "... zbinbin/net/Buffer.s"
	@echo "... zbinbin/net/Channel.o"
	@echo "... zbinbin/net/Channel.i"
	@echo "... zbinbin/net/Channel.s"
	@echo "... zbinbin/net/EventLoop.o"
	@echo "... zbinbin/net/EventLoop.i"
	@echo "... zbinbin/net/EventLoop.s"
	@echo "... zbinbin/net/EventLoopThread.o"
	@echo "... zbinbin/net/EventLoopThread.i"
	@echo "... zbinbin/net/EventLoopThread.s"
	@echo "... zbinbin/net/EventLoopThreadPool.o"
	@echo "... zbinbin/net/EventLoopThreadPool.i"
	@echo "... zbinbin/net/EventLoopThreadPool.s"
	@echo "... zbinbin/net/InetAddress.o"
	@echo "... zbinbin/net/InetAddress.i"
	@echo "... zbinbin/net/InetAddress.s"
	@echo "... zbinbin/net/Poller.o"
	@echo "... zbinbin/net/Poller.i"
	@echo "... zbinbin/net/Poller.s"
	@echo "... zbinbin/net/Socket.o"
	@echo "... zbinbin/net/Socket.i"
	@echo "... zbinbin/net/Socket.s"
	@echo "... zbinbin/net/SocketOps.o"
	@echo "... zbinbin/net/SocketOps.i"
	@echo "... zbinbin/net/SocketOps.s"
	@echo "... zbinbin/net/TcpConnection.o"
	@echo "... zbinbin/net/TcpConnection.i"
	@echo "... zbinbin/net/TcpConnection.s"
	@echo "... zbinbin/net/TcpServer.o"
	@echo "... zbinbin/net/TcpServer.i"
	@echo "... zbinbin/net/TcpServer.s"
	@echo "... zbinbin/thread/Condition.o"
	@echo "... zbinbin/thread/Condition.i"
	@echo "... zbinbin/thread/Condition.s"
	@echo "... zbinbin/thread/CountDownLatch.o"
	@echo "... zbinbin/thread/CountDownLatch.i"
	@echo "... zbinbin/thread/CountDownLatch.s"
	@echo "... zbinbin/thread/CurrentThread.o"
	@echo "... zbinbin/thread/CurrentThread.i"
	@echo "... zbinbin/thread/CurrentThread.s"
	@echo "... zbinbin/thread/Thread.o"
	@echo "... zbinbin/thread/Thread.i"
	@echo "... zbinbin/thread/Thread.s"
	@echo "... zbinbin/utility/Timestamp.o"
	@echo "... zbinbin/utility/Timestamp.i"
	@echo "... zbinbin/utility/Timestamp.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

