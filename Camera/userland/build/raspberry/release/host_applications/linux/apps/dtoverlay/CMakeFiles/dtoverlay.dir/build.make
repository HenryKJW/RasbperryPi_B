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
include host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/depend.make

# Include the progress variables for this target.
include host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/progress.make

# Include the compile flags for this target's objects.
include host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/flags.make

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o: host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/flags.make
host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o: ../../../host_applications/linux/apps/dtoverlay/dtoverlay_main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/git_server/Camera/userland/build/raspberry/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/apps/dtoverlay && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o   -c /home/pi/git_server/Camera/userland/host_applications/linux/apps/dtoverlay/dtoverlay_main.c

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dtoverlay.dir/dtoverlay_main.c.i"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/apps/dtoverlay && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/git_server/Camera/userland/host_applications/linux/apps/dtoverlay/dtoverlay_main.c > CMakeFiles/dtoverlay.dir/dtoverlay_main.c.i

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dtoverlay.dir/dtoverlay_main.c.s"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/apps/dtoverlay && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/git_server/Camera/userland/host_applications/linux/apps/dtoverlay/dtoverlay_main.c -o CMakeFiles/dtoverlay.dir/dtoverlay_main.c.s

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o.requires:
.PHONY : host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o.requires

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o.provides: host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o.requires
	$(MAKE) -f host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/build.make host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o.provides.build
.PHONY : host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o.provides

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o.provides.build: host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.o: host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/flags.make
host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.o: ../../../host_applications/linux/apps/dtoverlay/utils.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/git_server/Camera/userland/build/raspberry/release/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.o"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/apps/dtoverlay && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/dtoverlay.dir/utils.c.o   -c /home/pi/git_server/Camera/userland/host_applications/linux/apps/dtoverlay/utils.c

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dtoverlay.dir/utils.c.i"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/apps/dtoverlay && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/git_server/Camera/userland/host_applications/linux/apps/dtoverlay/utils.c > CMakeFiles/dtoverlay.dir/utils.c.i

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dtoverlay.dir/utils.c.s"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/apps/dtoverlay && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/git_server/Camera/userland/host_applications/linux/apps/dtoverlay/utils.c -o CMakeFiles/dtoverlay.dir/utils.c.s

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.o.requires:
.PHONY : host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.o.requires

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.o.provides: host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.o.requires
	$(MAKE) -f host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/build.make host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.o.provides.build
.PHONY : host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.o.provides

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.o.provides.build: host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.o

# Object files for target dtoverlay
dtoverlay_OBJECTS = \
"CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o" \
"CMakeFiles/dtoverlay.dir/utils.c.o"

# External object files for target dtoverlay
dtoverlay_EXTERNAL_OBJECTS =

../../bin/dtoverlay: host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o
../../bin/dtoverlay: host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.o
../../bin/dtoverlay: host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/build.make
../../bin/dtoverlay: ../../lib/libdtovl.so
../../bin/dtoverlay: ../../lib/libfdt.a
../../bin/dtoverlay: host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../../../../../../bin/dtoverlay"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/apps/dtoverlay && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dtoverlay.dir/link.txt --verbose=$(VERBOSE)
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/apps/dtoverlay && ln -sf dtoverlay dtparam
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/apps/dtoverlay && /usr/bin/cmake -E copy /home/pi/git_server/Camera/userland/host_applications/linux/apps/dtoverlay/dtoverlay-pre /home/pi/git_server/Camera/userland/build/raspberry/release/../../bin/dtoverlay-pre
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/apps/dtoverlay && /usr/bin/cmake -E copy /home/pi/git_server/Camera/userland/host_applications/linux/apps/dtoverlay/dtoverlay-post /home/pi/git_server/Camera/userland/build/raspberry/release/../../bin/dtoverlay-post

# Rule to build all files generated by this target.
host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/build: ../../bin/dtoverlay
.PHONY : host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/build

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/requires: host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/dtoverlay_main.c.o.requires
host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/requires: host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/utils.c.o.requires
.PHONY : host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/requires

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/clean:
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/apps/dtoverlay && $(CMAKE_COMMAND) -P CMakeFiles/dtoverlay.dir/cmake_clean.cmake
.PHONY : host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/clean

host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/depend:
	cd /home/pi/git_server/Camera/userland/build/raspberry/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/git_server/Camera/userland /home/pi/git_server/Camera/userland/host_applications/linux/apps/dtoverlay /home/pi/git_server/Camera/userland/build/raspberry/release /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/apps/dtoverlay /home/pi/git_server/Camera/userland/build/raspberry/release/host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : host_applications/linux/apps/dtoverlay/CMakeFiles/dtoverlay.dir/depend

