# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# Include any dependencies generated for this target.
include CMakeFiles/zbinbin.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/zbinbin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/zbinbin.dir/flags.make

CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o: CMakeFiles/zbinbin.dir/flags.make
CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o: zbinbin/log/log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/share/zbinbin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o -c /home/sam/share/zbinbin/zbinbin/log/log.cpp

CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/share/zbinbin/zbinbin/log/log.cpp > CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.i

CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/share/zbinbin/zbinbin/log/log.cpp -o CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.s

CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o.requires:

.PHONY : CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o.requires

CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o.provides: CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o.requires
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o.provides.build
.PHONY : CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o.provides

CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o.provides.build: CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o


CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o: CMakeFiles/zbinbin.dir/flags.make
CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o: zbinbin/log/LogStream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/share/zbinbin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o -c /home/sam/share/zbinbin/zbinbin/log/LogStream.cpp

CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/share/zbinbin/zbinbin/log/LogStream.cpp > CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.i

CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/share/zbinbin/zbinbin/log/LogStream.cpp -o CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.s

CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o.requires:

.PHONY : CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o.requires

CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o.provides: CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o.requires
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o.provides.build
.PHONY : CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o.provides

CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o.provides.build: CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o


CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o: CMakeFiles/zbinbin.dir/flags.make
CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o: zbinbin/thread/Thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/share/zbinbin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o -c /home/sam/share/zbinbin/zbinbin/thread/Thread.cpp

CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/share/zbinbin/zbinbin/thread/Thread.cpp > CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.i

CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/share/zbinbin/zbinbin/thread/Thread.cpp -o CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.s

CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o.requires:

.PHONY : CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o.requires

CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o.provides: CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o.requires
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o.provides.build
.PHONY : CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o.provides

CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o.provides.build: CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o


CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o: CMakeFiles/zbinbin.dir/flags.make
CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o: zbinbin/thread/Condition.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/share/zbinbin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o -c /home/sam/share/zbinbin/zbinbin/thread/Condition.cpp

CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/share/zbinbin/zbinbin/thread/Condition.cpp > CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.i

CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/share/zbinbin/zbinbin/thread/Condition.cpp -o CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.s

CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o.requires:

.PHONY : CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o.requires

CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o.provides: CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o.requires
	$(MAKE) -f CMakeFiles/zbinbin.dir/build.make CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o.provides.build
.PHONY : CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o.provides

CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o.provides.build: CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o


# Object files for target zbinbin
zbinbin_OBJECTS = \
"CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o" \
"CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o" \
"CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o" \
"CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o"

# External object files for target zbinbin
zbinbin_EXTERNAL_OBJECTS =

lib/libzbinbin.so: CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o
lib/libzbinbin.so: CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o
lib/libzbinbin.so: CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o
lib/libzbinbin.so: CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o
lib/libzbinbin.so: CMakeFiles/zbinbin.dir/build.make
lib/libzbinbin.so: CMakeFiles/zbinbin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sam/share/zbinbin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library lib/libzbinbin.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zbinbin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/zbinbin.dir/build: lib/libzbinbin.so

.PHONY : CMakeFiles/zbinbin.dir/build

CMakeFiles/zbinbin.dir/requires: CMakeFiles/zbinbin.dir/zbinbin/log/log.cpp.o.requires
CMakeFiles/zbinbin.dir/requires: CMakeFiles/zbinbin.dir/zbinbin/log/LogStream.cpp.o.requires
CMakeFiles/zbinbin.dir/requires: CMakeFiles/zbinbin.dir/zbinbin/thread/Thread.cpp.o.requires
CMakeFiles/zbinbin.dir/requires: CMakeFiles/zbinbin.dir/zbinbin/thread/Condition.cpp.o.requires

.PHONY : CMakeFiles/zbinbin.dir/requires

CMakeFiles/zbinbin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/zbinbin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/zbinbin.dir/clean

CMakeFiles/zbinbin.dir/depend:
	cd /home/sam/share/zbinbin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sam/share/zbinbin /home/sam/share/zbinbin /home/sam/share/zbinbin /home/sam/share/zbinbin /home/sam/share/zbinbin/CMakeFiles/zbinbin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/zbinbin.dir/depend

