# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /home/kecy/bin/cmake

# The command to remove a file.
RM = /home/kecy/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/tmp.76Xyk3tz3c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.76Xyk3tz3c/cmake-build-debug-remote-host

# Include any dependencies generated for this target.
include CMakeFiles/ExampleCTP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ExampleCTP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ExampleCTP.dir/flags.make

CMakeFiles/ExampleCTP.dir/example/cpp/CTP/example_ctp.cpp.o: CMakeFiles/ExampleCTP.dir/flags.make
CMakeFiles/ExampleCTP.dir/example/cpp/CTP/example_ctp.cpp.o: ../example/cpp/CTP/example_ctp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.76Xyk3tz3c/cmake-build-debug-remote-host/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ExampleCTP.dir/example/cpp/CTP/example_ctp.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ExampleCTP.dir/example/cpp/CTP/example_ctp.cpp.o -c /tmp/tmp.76Xyk3tz3c/example/cpp/CTP/example_ctp.cpp

CMakeFiles/ExampleCTP.dir/example/cpp/CTP/example_ctp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ExampleCTP.dir/example/cpp/CTP/example_ctp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.76Xyk3tz3c/example/cpp/CTP/example_ctp.cpp > CMakeFiles/ExampleCTP.dir/example/cpp/CTP/example_ctp.cpp.i

CMakeFiles/ExampleCTP.dir/example/cpp/CTP/example_ctp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ExampleCTP.dir/example/cpp/CTP/example_ctp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.76Xyk3tz3c/example/cpp/CTP/example_ctp.cpp -o CMakeFiles/ExampleCTP.dir/example/cpp/CTP/example_ctp.cpp.s

# Object files for target ExampleCTP
ExampleCTP_OBJECTS = \
"CMakeFiles/ExampleCTP.dir/example/cpp/CTP/example_ctp.cpp.o"

# External object files for target ExampleCTP
ExampleCTP_EXTERNAL_OBJECTS =

bin/ExampleCTP: CMakeFiles/ExampleCTP.dir/example/cpp/CTP/example_ctp.cpp.o
bin/ExampleCTP: CMakeFiles/ExampleCTP.dir/build.make
bin/ExampleCTP: lib/libXAPI_CPP.so
bin/ExampleCTP: CMakeFiles/ExampleCTP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.76Xyk3tz3c/cmake-build-debug-remote-host/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/ExampleCTP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ExampleCTP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ExampleCTP.dir/build: bin/ExampleCTP

.PHONY : CMakeFiles/ExampleCTP.dir/build

CMakeFiles/ExampleCTP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ExampleCTP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ExampleCTP.dir/clean

CMakeFiles/ExampleCTP.dir/depend:
	cd /tmp/tmp.76Xyk3tz3c/cmake-build-debug-remote-host && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.76Xyk3tz3c /tmp/tmp.76Xyk3tz3c /tmp/tmp.76Xyk3tz3c/cmake-build-debug-remote-host /tmp/tmp.76Xyk3tz3c/cmake-build-debug-remote-host /tmp/tmp.76Xyk3tz3c/cmake-build-debug-remote-host/CMakeFiles/ExampleCTP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ExampleCTP.dir/depend
