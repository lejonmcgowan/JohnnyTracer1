# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lejonmcgowan/ClionProjects/RayTracer473

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lejonmcgowan/ClionProjects/RayTracer473/build

# Include any dependencies generated for this target.
include test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/depend.make

# Include the progress variables for this target.
include test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/progress.make

# Include the compile flags for this target's objects.
include test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/flags.make

test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o: test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/flags.make
test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o: ../ext/googletest/googletest/src/gtest_main.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lejonmcgowan/ClionProjects/RayTracer473/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o"
	cd /home/lejonmcgowan/ClionProjects/RayTracer473/build/test/ext/googletest/googlemock/gtest && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gtest_main.dir/src/gtest_main.cc.o -c /home/lejonmcgowan/ClionProjects/RayTracer473/ext/googletest/googletest/src/gtest_main.cc

test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest_main.dir/src/gtest_main.cc.i"
	cd /home/lejonmcgowan/ClionProjects/RayTracer473/build/test/ext/googletest/googlemock/gtest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lejonmcgowan/ClionProjects/RayTracer473/ext/googletest/googletest/src/gtest_main.cc > CMakeFiles/gtest_main.dir/src/gtest_main.cc.i

test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest_main.dir/src/gtest_main.cc.s"
	cd /home/lejonmcgowan/ClionProjects/RayTracer473/build/test/ext/googletest/googlemock/gtest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lejonmcgowan/ClionProjects/RayTracer473/ext/googletest/googletest/src/gtest_main.cc -o CMakeFiles/gtest_main.dir/src/gtest_main.cc.s

test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.requires:
.PHONY : test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.requires

test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.provides: test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.requires
	$(MAKE) -f test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/build.make test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.provides.build
.PHONY : test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.provides

test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.provides.build: test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o

# Object files for target gtest_main
gtest_main_OBJECTS = \
"CMakeFiles/gtest_main.dir/src/gtest_main.cc.o"

# External object files for target gtest_main
gtest_main_EXTERNAL_OBJECTS =

lib/libgtest_main.a: test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
lib/libgtest_main.a: test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/build.make
lib/libgtest_main.a: test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../../../../lib/libgtest_main.a"
	cd /home/lejonmcgowan/ClionProjects/RayTracer473/build/test/ext/googletest/googlemock/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest_main.dir/cmake_clean_target.cmake
	cd /home/lejonmcgowan/ClionProjects/RayTracer473/build/test/ext/googletest/googlemock/gtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/build: lib/libgtest_main.a
.PHONY : test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/build

test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/requires: test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.requires
.PHONY : test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/requires

test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/clean:
	cd /home/lejonmcgowan/ClionProjects/RayTracer473/build/test/ext/googletest/googlemock/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest_main.dir/cmake_clean.cmake
.PHONY : test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/clean

test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/depend:
	cd /home/lejonmcgowan/ClionProjects/RayTracer473/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lejonmcgowan/ClionProjects/RayTracer473 /home/lejonmcgowan/ClionProjects/RayTracer473/ext/googletest/googletest /home/lejonmcgowan/ClionProjects/RayTracer473/build /home/lejonmcgowan/ClionProjects/RayTracer473/build/test/ext/googletest/googlemock/gtest /home/lejonmcgowan/ClionProjects/RayTracer473/build/test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/ext/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/depend

