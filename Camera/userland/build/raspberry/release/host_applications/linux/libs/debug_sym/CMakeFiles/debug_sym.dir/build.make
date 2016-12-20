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
include host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/depend.make

# Include the progress variables for this target.
include host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/progress.make

# Include the compile flags for this target's objects.
include host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/flags.make

host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.o: host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/flags.make
host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.o: ../../../host_applications/linux/libs/debug_sym/debug_sym.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/git_server/Camera/userland/build/raspberry/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.o"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/libs/debug_sym && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/debug_sym.dir/debug_sym.c.o   -c /home/pi/git_server/Camera/userland/host_applications/linux/libs/debug_sym/debug_sym.c

host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/debug_sym.dir/debug_sym.c.i"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/libs/debug_sym && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/git_server/Camera/userland/host_applications/linux/libs/debug_sym/debug_sym.c > CMakeFiles/debug_sym.dir/debug_sym.c.i

host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/debug_sym.dir/debug_sym.c.s"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/libs/debug_sym && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/git_server/Camera/userland/host_applications/linux/libs/debug_sym/debug_sym.c -o CMakeFiles/debug_sym.dir/debug_sym.c.s

host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.o.requires:
.PHONY : host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.o.requires

host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.o.provides: host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.o.requires
	$(MAKE) -f host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/build.make host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.o.provides.build
.PHONY : host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.o.provides

host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.o.provides.build: host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.o

# Object files for target debug_sym
debug_sym_OBJECTS = \
"CMakeFiles/debug_sym.dir/debug_sym.c.o"

# External object files for target debug_sym
debug_sym_EXTERNAL_OBJECTS =

../../lib/libdebug_sym.so: host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.o
../../lib/libdebug_sym.so: host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/build.make
../../lib/libdebug_sym.so: host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library ../../../../../../lib/libdebug_sym.so"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/libs/debug_sym && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/debug_sym.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/build: ../../lib/libdebug_sym.so
.PHONY : host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/build

host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/requires: host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/debug_sym.c.o.requires
.PHONY : host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/requires

host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/clean:
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/libs/debug_sym && $(CMAKE_COMMAND) -P CMakeFiles/debug_sym.dir/cmake_clean.cmake
.PHONY : host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/clean

host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/depend:
	cd /home/pi/git_server/Camera/userland/build/raspberry/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/git_server/Camera/userland /home/pi/git_server/Camera/userland/host_applications/linux/libs/debug_sym /home/pi/git_server/Camera/userland/build/raspberry/release /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/libs/debug_sym /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : host_applications/linux/libs/debug_sym/CMakeFiles/debug_sym.dir/depend

