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
include helpers/dtoverlay/CMakeFiles/dtovl.dir/depend.make

# Include the progress variables for this target.
include helpers/dtoverlay/CMakeFiles/dtovl.dir/progress.make

# Include the compile flags for this target's objects.
include helpers/dtoverlay/CMakeFiles/dtovl.dir/flags.make

helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.o: helpers/dtoverlay/CMakeFiles/dtovl.dir/flags.make
helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.o: ../../../helpers/dtoverlay/dtoverlay.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/git_server/Camera/userland/build/raspberry/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.o"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/helpers/dtoverlay && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/dtovl.dir/dtoverlay.c.o   -c /home/pi/git_server/Camera/userland/helpers/dtoverlay/dtoverlay.c

helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dtovl.dir/dtoverlay.c.i"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/helpers/dtoverlay && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/git_server/Camera/userland/helpers/dtoverlay/dtoverlay.c > CMakeFiles/dtovl.dir/dtoverlay.c.i

helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dtovl.dir/dtoverlay.c.s"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/helpers/dtoverlay && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/git_server/Camera/userland/helpers/dtoverlay/dtoverlay.c -o CMakeFiles/dtovl.dir/dtoverlay.c.s

helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.o.requires:
.PHONY : helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.o.requires

helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.o.provides: helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.o.requires
	$(MAKE) -f helpers/dtoverlay/CMakeFiles/dtovl.dir/build.make helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.o.provides.build
.PHONY : helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.o.provides

helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.o.provides.build: helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.o

# Object files for target dtovl
dtovl_OBJECTS = \
"CMakeFiles/dtovl.dir/dtoverlay.c.o"

# External object files for target dtovl
dtovl_EXTERNAL_OBJECTS =

../../lib/libdtovl.so: helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.o
../../lib/libdtovl.so: helpers/dtoverlay/CMakeFiles/dtovl.dir/build.make
../../lib/libdtovl.so: ../../lib/libfdt.a
../../lib/libdtovl.so: helpers/dtoverlay/CMakeFiles/dtovl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library ../../../../lib/libdtovl.so"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/helpers/dtoverlay && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dtovl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
helpers/dtoverlay/CMakeFiles/dtovl.dir/build: ../../lib/libdtovl.so
.PHONY : helpers/dtoverlay/CMakeFiles/dtovl.dir/build

helpers/dtoverlay/CMakeFiles/dtovl.dir/requires: helpers/dtoverlay/CMakeFiles/dtovl.dir/dtoverlay.c.o.requires
.PHONY : helpers/dtoverlay/CMakeFiles/dtovl.dir/requires

helpers/dtoverlay/CMakeFiles/dtovl.dir/clean:
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/helpers/dtoverlay && $(CMAKE_COMMAND) -P CMakeFiles/dtovl.dir/cmake_clean.cmake
.PHONY : helpers/dtoverlay/CMakeFiles/dtovl.dir/clean

helpers/dtoverlay/CMakeFiles/dtovl.dir/depend:
	cd /home/pi/git_server/Camera/userland/build/raspberry/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/git_server/Camera/userland /home/pi/git_server/Camera/userland/helpers/dtoverlay /home/pi/git_server/Camera/userland/build/raspberry/release /home/pi/git_server/Camera/userland/build/raspberry/release/helpers/dtoverlay /home/pi/git_server/Camera/userland/build/raspberry/release/helpers/dtoverlay/CMakeFiles/dtovl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : helpers/dtoverlay/CMakeFiles/dtovl.dir/depend

