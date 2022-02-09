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
CMAKE_SOURCE_DIR = /home/sam/share/zbinbin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sam/share/zbinbin

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
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sam/share/zbinbin/CMakeFiles /home/sam/share/zbinbin/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sam/share/zbinbin/CMakeFiles 0
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
# Target rules for targets named thread_test

# Build rule for target.
thread_test: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 thread_test
.PHONY : thread_test

# fast build rule for target.
thread_test/fast:
	$(MAKE) -f CMakeFiles/thread_test.dir/build.make CMakeFiles/thread_test.dir/build
.PHONY : thread_test/fast

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
# Target rules for targets named test

# Build rule for target.
test: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test
.PHONY : test

# fast build rule for target.
test/fast:
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/build
.PHONY : test/fast

tests/test.o: tests/test.cpp.o

.PHONY : tests/test.o

# target to build an object file
tests/test.cpp.o:
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cpp.o
.PHONY : tests/test.cpp.o

tests/test.i: tests/test.cpp.i

.PHONY : tests/test.i

# target to preprocess a source file
tests/test.cpp.i:
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cpp.i
.PHONY : tests/test.cpp.i

tests/test.s: tests/test.cpp.s

.PHONY : tests/test.s

# target to generate assembly for a file
tests/test.cpp.s:
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cpp.s
.PHONY : tests/test.cpp.s

tests/thread.o: tests/thread.cpp.o

.PHONY : tests/thread.o

# target to build an object file
tests/thread.cpp.o:
	$(MAKE) -f CMakeFiles/thread_test.dir/build.make CMakeFiles/thread_test.dir/tests/thread.cpp.o
.PHONY : tests/thread.cpp.o

tests/thread.i: tests/thread.cpp.i

.PHONY : tests/thread.i

# target to preprocess a source file
tests/thread.cpp.i:
	$(MAKE) -f CMakeFiles/thread_test.dir/build.make CMakeFiles/thread_test.dir/tests/thread.cpp.i
.PHONY : tests/thread.cpp.i

tests/thread.s: tests/thread.cpp.s

.PHONY : tests/thread.s

# target to generate assembly for a file
tests/thread.cpp.s:
	$(MAKE) -f CMakeFiles/thread_test.dir/build.make CMakeFiles/thread_test.dir/tests/thread.cpp.s
.PHONY : tests/thread.cpp.s

zbinbin/log/log.o: zbinbin/log/log.cpp.o

.PHONY : zbinbin/log/log.o

# target to build an object file
zbinbin/log/log.cpp.o:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o
.PHONY : zbinbin/log/log.cpp.o

zbinbin/log/log.i: zbinbin/log/log.cpp.i

.PHONY : zbinbin/log/log.i

# target to preprocess a source file
zbinbin/log/log.cpp.i:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.i
.PHONY : zbinbin/log/log.cpp.i

zbinbin/log/log.s: zbinbin/log/log.cpp.s

.PHONY : zbinbin/log/log.s

# target to generate assembly for a file
zbinbin/log/log.cpp.s:
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.s
.PHONY : zbinbin/log/log.cpp.s

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

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... thread_test"
	@echo "... zbinbin"
	@echo "... test"
	@echo "... tests/test.o"
	@echo "... tests/test.i"
	@echo "... tests/test.s"
	@echo "... tests/thread.o"
	@echo "... tests/thread.i"
	@echo "... tests/thread.s"
	@echo "... zbinbin/log/log.o"
	@echo "... zbinbin/log/log.i"
	@echo "... zbinbin/log/log.s"
	@echo "... zbinbin/thread/Condition.o"
	@echo "... zbinbin/thread/Condition.i"
	@echo "... zbinbin/thread/Condition.s"
	@echo "... zbinbin/thread/Thread.o"
	@echo "... zbinbin/thread/Thread.i"
	@echo "... zbinbin/thread/Thread.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

