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
CMAKE_SOURCE_DIR = /home/binwatson/share/zbinbin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/binwatson/share/zbinbin

# Include any dependencies generated for this target.
include CMakeFiles/HttpRequest_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HttpRequest_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HttpRequest_test.dir/flags.make

CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o: CMakeFiles/HttpRequest_test.dir/flags.make
CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o: zbinbin/http/tests/HttpRequest_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/binwatson/share/zbinbin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o -c /home/binwatson/share/zbinbin/zbinbin/http/tests/HttpRequest_test.cpp

CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/binwatson/share/zbinbin/zbinbin/http/tests/HttpRequest_test.cpp > CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.i

CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/binwatson/share/zbinbin/zbinbin/http/tests/HttpRequest_test.cpp -o CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.s

CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o.requires:

.PHONY : CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o.requires

CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o.provides: CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o.requires
	$(MAKE) -f CMakeFiles/HttpRequest_test.dir/build.make CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o.provides.build
.PHONY : CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o.provides

CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o.provides.build: CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o


# Object files for target HttpRequest_test
HttpRequest_test_OBJECTS = \
"CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o"

# External object files for target HttpRequest_test
HttpRequest_test_EXTERNAL_OBJECTS =

bin/HttpRequest_test: CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o
bin/HttpRequest_test: CMakeFiles/HttpRequest_test.dir/build.make
bin/HttpRequest_test: lib/libzbinbin.so
bin/HttpRequest_test: CMakeFiles/HttpRequest_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/binwatson/share/zbinbin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/HttpRequest_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HttpRequest_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HttpRequest_test.dir/build: bin/HttpRequest_test

.PHONY : CMakeFiles/HttpRequest_test.dir/build

CMakeFiles/HttpRequest_test.dir/requires: CMakeFiles/HttpRequest_test.dir/zbinbin/http/tests/HttpRequest_test.cpp.o.requires

.PHONY : CMakeFiles/HttpRequest_test.dir/requires

CMakeFiles/HttpRequest_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HttpRequest_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HttpRequest_test.dir/clean

CMakeFiles/HttpRequest_test.dir/depend:
	cd /home/binwatson/share/zbinbin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/binwatson/share/zbinbin /home/binwatson/share/zbinbin /home/binwatson/share/zbinbin /home/binwatson/share/zbinbin /home/binwatson/share/zbinbin/CMakeFiles/HttpRequest_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HttpRequest_test.dir/depend

