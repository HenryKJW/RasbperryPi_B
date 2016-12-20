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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/git_server/Camera/userland

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/git_server/Camera/userland/build/raspberry/release

# Include any dependencies generated for this target.
include interface/vchiq_arm/CMakeFiles/vchiq_test.dir/depend.make

# Include the progress variables for this target.
include interface/vchiq_arm/CMakeFiles/vchiq_test.dir/progress.make

# Include the compile flags for this target's objects.
include interface/vchiq_arm/CMakeFiles/vchiq_test.dir/flags.make

interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.o: interface/vchiq_arm/CMakeFiles/vchiq_test.dir/flags.make
interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.o: ../../../interface/vchiq_arm/vchiq_test.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/git_server/Camera/userland/build/raspberry/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.o"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/vchiq_arm && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/vchiq_test.dir/vchiq_test.c.o   -c /home/pi/git_server/Camera/userland/interface/vchiq_arm/vchiq_test.c

interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vchiq_test.dir/vchiq_test.c.i"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/vchiq_arm && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/git_server/Camera/userland/interface/vchiq_arm/vchiq_test.c > CMakeFiles/vchiq_test.dir/vchiq_test.c.i

interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vchiq_test.dir/vchiq_test.c.s"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/vchiq_arm && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/git_server/Camera/userland/interface/vchiq_arm/vchiq_test.c -o CMakeFiles/vchiq_test.dir/vchiq_test.c.s

interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.o.requires:
.PHONY : interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.o.requires

interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.o.provides: interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.o.requires
	$(MAKE) -f interface/vchiq_arm/CMakeFiles/vchiq_test.dir/build.make interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.o.provides.build
.PHONY : interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.o.provides

interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.o.provides.build: interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.o

# Object files for target vchiq_test
vchiq_test_OBJECTS = \
"CMakeFiles/vchiq_test.dir/vchiq_test.c.o"

# External object files for target vchiq_test
vchiq_test_EXTERNAL_OBJECTS =

../../bin/vchiq_test: interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.o
../../bin/vchiq_test: interface/vchiq_arm/CMakeFiles/vchiq_test.dir/build.make
../../bin/vchiq_test: ../../lib/libvchiq_arm.so
../../bin/vchiq_test: ../../lib/libvcos.so
../../bin/vchiq_test: interface/vchiq_arm/CMakeFiles/vchiq_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../../../../bin/vchiq_test"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/vchiq_arm && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vchiq_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
interface/vchiq_arm/CMakeFiles/vchiq_test.dir/build: ../../bin/vchiq_test
.PHONY : interface/vchiq_arm/CMakeFiles/vchiq_test.dir/build

interface/vchiq_arm/CMakeFiles/vchiq_test.dir/requires: interface/vchiq_arm/CMakeFiles/vchiq_test.dir/vchiq_test.c.o.requires
.PHONY : interface/vchiq_arm/CMakeFiles/vchiq_test.dir/requires

interface/vchiq_arm/CMakeFiles/vchiq_test.dir/clean:
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/vchiq_arm && $(CMAKE_COMMAND) -P CMakeFiles/vchiq_test.dir/cmake_clean.cmake
.PHONY : interface/vchiq_arm/CMakeFiles/vchiq_test.dir/clean

interface/vchiq_arm/CMakeFiles/vchiq_test.dir/depend:
	cd /home/pi/git_server/Camera/userland/build/raspberry/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/git_server/Camera/userland /home/pi/git_server/Camera/userland/interface/vchiq_arm /home/pi/git_server/Camera/userland/build/raspberry/release /home/pi/git_server/Camera/userland/build/raspberry/release/interface/vchiq_arm /home/pi/git_server/Camera/userland/build/raspberry/release/interface/vchiq_arm/CMakeFiles/vchiq_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : interface/vchiq_arm/CMakeFiles/vchiq_test.dir/depend

