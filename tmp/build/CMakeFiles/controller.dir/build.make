# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/james/osrf/Reveal/tmp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/james/osrf/Reveal/tmp/build

# Include any dependencies generated for this target.
include CMakeFiles/controller.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/controller.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/controller.dir/flags.make

CMakeFiles/controller.dir/controller.cpp.o: CMakeFiles/controller.dir/flags.make
CMakeFiles/controller.dir/controller.cpp.o: ../controller.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/james/osrf/Reveal/tmp/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/controller.dir/controller.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/controller.dir/controller.cpp.o -c /home/james/osrf/Reveal/tmp/controller.cpp

CMakeFiles/controller.dir/controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/controller.dir/controller.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/james/osrf/Reveal/tmp/controller.cpp > CMakeFiles/controller.dir/controller.cpp.i

CMakeFiles/controller.dir/controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/controller.dir/controller.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/james/osrf/Reveal/tmp/controller.cpp -o CMakeFiles/controller.dir/controller.cpp.s

CMakeFiles/controller.dir/controller.cpp.o.requires:
.PHONY : CMakeFiles/controller.dir/controller.cpp.o.requires

CMakeFiles/controller.dir/controller.cpp.o.provides: CMakeFiles/controller.dir/controller.cpp.o.requires
	$(MAKE) -f CMakeFiles/controller.dir/build.make CMakeFiles/controller.dir/controller.cpp.o.provides.build
.PHONY : CMakeFiles/controller.dir/controller.cpp.o.provides

CMakeFiles/controller.dir/controller.cpp.o.provides.build: CMakeFiles/controller.dir/controller.cpp.o

# Object files for target controller
controller_OBJECTS = \
"CMakeFiles/controller.dir/controller.cpp.o"

# External object files for target controller
controller_EXTERNAL_OBJECTS =

libcontroller.so: CMakeFiles/controller.dir/controller.cpp.o
libcontroller.so: /usr/local/lib/librevealcore.so
libcontroller.so: CMakeFiles/controller.dir/build.make
libcontroller.so: CMakeFiles/controller.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libcontroller.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/controller.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/controller.dir/build: libcontroller.so
.PHONY : CMakeFiles/controller.dir/build

CMakeFiles/controller.dir/requires: CMakeFiles/controller.dir/controller.cpp.o.requires
.PHONY : CMakeFiles/controller.dir/requires

CMakeFiles/controller.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/controller.dir/cmake_clean.cmake
.PHONY : CMakeFiles/controller.dir/clean

CMakeFiles/controller.dir/depend:
	cd /home/james/osrf/Reveal/tmp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/james/osrf/Reveal/tmp /home/james/osrf/Reveal/tmp /home/james/osrf/Reveal/tmp/build /home/james/osrf/Reveal/tmp/build /home/james/osrf/Reveal/tmp/build/CMakeFiles/controller.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/controller.dir/depend
