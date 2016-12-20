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
include interface/khronos/CMakeFiles/brcmGLESv2.dir/depend.make

# Include the progress variables for this target.
include interface/khronos/CMakeFiles/brcmGLESv2.dir/progress.make

# Include the compile flags for this target's objects.
include interface/khronos/CMakeFiles/brcmGLESv2.dir/flags.make

interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o: interface/khronos/CMakeFiles/brcmGLESv2.dir/flags.make
interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o: ../../../interface/khronos/glxx/glxx_client.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/git_server/Camera/userland/build/raspberry/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/khronos && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o   -c /home/pi/git_server/Camera/userland/interface/khronos/glxx/glxx_client.c

interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.i"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/khronos && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/git_server/Camera/userland/interface/khronos/glxx/glxx_client.c > CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.i

interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.s"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/khronos && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/git_server/Camera/userland/interface/khronos/glxx/glxx_client.c -o CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.s

interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o.requires:
.PHONY : interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o.requires

interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o.provides: interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o.requires
	$(MAKE) -f interface/khronos/CMakeFiles/brcmGLESv2.dir/build.make interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o.provides.build
.PHONY : interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o.provides

interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o.provides.build: interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o

# Object files for target brcmGLESv2
brcmGLESv2_OBJECTS = \
"CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o"

# External object files for target brcmGLESv2
brcmGLESv2_EXTERNAL_OBJECTS =

../../lib/libbrcmGLESv2.so: interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o
../../lib/libbrcmGLESv2.so: interface/khronos/CMakeFiles/brcmGLESv2.dir/build.make
../../lib/libbrcmGLESv2.so: ../../lib/libbrcmEGL.so
../../lib/libbrcmGLESv2.so: ../../lib/libkhrn_client.a
../../lib/libbrcmGLESv2.so: ../../lib/libvcos.so
../../lib/libbrcmGLESv2.so: ../../lib/libbcm_host.so
../../lib/libbrcmGLESv2.so: ../../lib/libvchostif.a
../../lib/libbrcmGLESv2.so: ../../lib/libvchiq_arm.so
../../lib/libbrcmGLESv2.so: ../../lib/libvcos.so
../../lib/libbrcmGLESv2.so: ../../lib/libvcfiled_check.a
../../lib/libbrcmGLESv2.so: interface/khronos/CMakeFiles/brcmGLESv2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library ../../../../lib/libbrcmGLESv2.so"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/khronos && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/brcmGLESv2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
interface/khronos/CMakeFiles/brcmGLESv2.dir/build: ../../lib/libbrcmGLESv2.so
.PHONY : interface/khronos/CMakeFiles/brcmGLESv2.dir/build

interface/khronos/CMakeFiles/brcmGLESv2.dir/requires: interface/khronos/CMakeFiles/brcmGLESv2.dir/glxx/glxx_client.c.o.requires
.PHONY : interface/khronos/CMakeFiles/brcmGLESv2.dir/requires

interface/khronos/CMakeFiles/brcmGLESv2.dir/clean:
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/khronos && $(CMAKE_COMMAND) -P CMakeFiles/brcmGLESv2.dir/cmake_clean.cmake
.PHONY : interface/khronos/CMakeFiles/brcmGLESv2.dir/clean

interface/khronos/CMakeFiles/brcmGLESv2.dir/depend:
	cd /home/pi/git_server/Camera/userland/build/raspberry/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/git_server/Camera/userland /home/pi/git_server/Camera/userland/interface/khronos /home/pi/git_server/Camera/userland/build/raspberry/release /home/pi/git_server/Camera/userland/build/raspberry/release/interface/khronos /home/pi/git_server/Camera/userland/build/raspberry/release/interface/khronos/CMakeFiles/brcmGLESv2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : interface/khronos/CMakeFiles/brcmGLESv2.dir/depend

