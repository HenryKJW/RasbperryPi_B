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
include interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/depend.make

# Include the progress variables for this target.
include interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/progress.make

# Include the compile flags for this target's objects.
include interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/flags.make

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/flags.make
interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o: ../../../interface/mmal/openmaxil/mmalomx_util_params.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/git_server/Camera/userland/build/raspberry/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o   -c /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params.c

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.i"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params.c > CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.i

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.s"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params.c -o CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.s

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o.requires:
.PHONY : interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o.requires

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o.provides: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o.requires
	$(MAKE) -f interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/build.make interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o.provides.build
.PHONY : interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o.provides

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o.provides.build: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/flags.make
interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o: ../../../interface/mmal/openmaxil/mmalomx_util_params_audio.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/git_server/Camera/userland/build/raspberry/release/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o   -c /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params_audio.c

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.i"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params_audio.c > CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.i

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.s"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params_audio.c -o CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.s

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o.requires:
.PHONY : interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o.requires

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o.provides: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o.requires
	$(MAKE) -f interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/build.make interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o.provides.build
.PHONY : interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o.provides

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o.provides.build: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/flags.make
interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o: ../../../interface/mmal/openmaxil/mmalomx_util_params_video.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/git_server/Camera/userland/build/raspberry/release/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o   -c /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params_video.c

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.i"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params_video.c > CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.i

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.s"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params_video.c -o CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.s

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o.requires:
.PHONY : interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o.requires

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o.provides: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o.requires
	$(MAKE) -f interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/build.make interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o.provides.build
.PHONY : interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o.provides

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o.provides.build: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/flags.make
interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o: ../../../interface/mmal/openmaxil/mmalomx_util_params_camera.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/git_server/Camera/userland/build/raspberry/release/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o   -c /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params_camera.c

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.i"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params_camera.c > CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.i

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.s"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params_camera.c -o CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.s

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o.requires:
.PHONY : interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o.requires

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o.provides: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o.requires
	$(MAKE) -f interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/build.make interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o.provides.build
.PHONY : interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o.provides

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o.provides.build: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/flags.make
interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o: ../../../interface/mmal/openmaxil/mmalomx_util_params_misc.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/git_server/Camera/userland/build/raspberry/release/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o   -c /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params_misc.c

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.i"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params_misc.c > CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.i

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.s"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/git_server/Camera/userland/interface/mmal/openmaxil/mmalomx_util_params_misc.c -o CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.s

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o.requires:
.PHONY : interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o.requires

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o.provides: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o.requires
	$(MAKE) -f interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/build.make interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o.provides.build
.PHONY : interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o.provides

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o.provides.build: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o

# Object files for target mmal_omxutil
mmal_omxutil_OBJECTS = \
"CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o" \
"CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o" \
"CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o" \
"CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o" \
"CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o"

# External object files for target mmal_omxutil
mmal_omxutil_EXTERNAL_OBJECTS =

../../lib/libmmal_omxutil.so: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o
../../lib/libmmal_omxutil.so: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o
../../lib/libmmal_omxutil.so: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o
../../lib/libmmal_omxutil.so: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o
../../lib/libmmal_omxutil.so: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o
../../lib/libmmal_omxutil.so: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/build.make
../../lib/libmmal_omxutil.so: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library ../../../../../lib/libmmal_omxutil.so"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mmal_omxutil.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/build: ../../lib/libmmal_omxutil.so
.PHONY : interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/build

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/requires: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params.c.o.requires
interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/requires: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_audio.c.o.requires
interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/requires: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_video.c.o.requires
interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/requires: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_camera.c.o.requires
interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/requires: interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/mmalomx_util_params_misc.c.o.requires
.PHONY : interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/requires

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/clean:
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil && $(CMAKE_COMMAND) -P CMakeFiles/mmal_omxutil.dir/cmake_clean.cmake
.PHONY : interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/clean

interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/depend:
	cd /home/pi/git_server/Camera/userland/build/raspberry/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/git_server/Camera/userland /home/pi/git_server/Camera/userland/interface/mmal/openmaxil /home/pi/git_server/Camera/userland/build/raspberry/release /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil /home/pi/git_server/Camera/userland/build/raspberry/release/interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : interface/mmal/openmaxil/CMakeFiles/mmal_omxutil.dir/depend

