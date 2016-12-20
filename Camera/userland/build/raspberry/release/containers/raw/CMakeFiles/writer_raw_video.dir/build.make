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
include containers/raw/CMakeFiles/writer_raw_video.dir/depend.make

# Include the progress variables for this target.
include containers/raw/CMakeFiles/writer_raw_video.dir/progress.make

# Include the compile flags for this target's objects.
include containers/raw/CMakeFiles/writer_raw_video.dir/flags.make

containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o: containers/raw/CMakeFiles/writer_raw_video.dir/flags.make
containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o: ../../../containers/raw/raw_video_writer.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/git_server/Camera/userland/build/raspberry/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/containers/raw && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o   -c /home/pi/git_server/Camera/userland/containers/raw/raw_video_writer.c

containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/writer_raw_video.dir/raw_video_writer.c.i"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/containers/raw && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/git_server/Camera/userland/containers/raw/raw_video_writer.c > CMakeFiles/writer_raw_video.dir/raw_video_writer.c.i

containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/writer_raw_video.dir/raw_video_writer.c.s"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/containers/raw && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/git_server/Camera/userland/containers/raw/raw_video_writer.c -o CMakeFiles/writer_raw_video.dir/raw_video_writer.c.s

containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o.requires:
.PHONY : containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o.requires

containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o.provides: containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o.requires
	$(MAKE) -f containers/raw/CMakeFiles/writer_raw_video.dir/build.make containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o.provides.build
.PHONY : containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o.provides

containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o.provides.build: containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o

# Object files for target writer_raw_video
writer_raw_video_OBJECTS = \
"CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o"

# External object files for target writer_raw_video
writer_raw_video_EXTERNAL_OBJECTS =

../../lib/writer_raw_video.so: containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o
../../lib/writer_raw_video.so: containers/raw/CMakeFiles/writer_raw_video.dir/build.make
../../lib/writer_raw_video.so: ../../lib/libcontainers.so
../../lib/writer_raw_video.so: ../../lib/libvcos.so
../../lib/writer_raw_video.so: containers/raw/CMakeFiles/writer_raw_video.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library ../../../../lib/writer_raw_video.so"
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/containers/raw && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/writer_raw_video.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
containers/raw/CMakeFiles/writer_raw_video.dir/build: ../../lib/writer_raw_video.so
.PHONY : containers/raw/CMakeFiles/writer_raw_video.dir/build

containers/raw/CMakeFiles/writer_raw_video.dir/requires: containers/raw/CMakeFiles/writer_raw_video.dir/raw_video_writer.c.o.requires
.PHONY : containers/raw/CMakeFiles/writer_raw_video.dir/requires

containers/raw/CMakeFiles/writer_raw_video.dir/clean:
	cd /home/pi/git_server/Camera/userland/build/raspberry/release/containers/raw && $(CMAKE_COMMAND) -P CMakeFiles/writer_raw_video.dir/cmake_clean.cmake
.PHONY : containers/raw/CMakeFiles/writer_raw_video.dir/clean

containers/raw/CMakeFiles/writer_raw_video.dir/depend:
	cd /home/pi/git_server/Camera/userland/build/raspberry/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/git_server/Camera/userland /home/pi/git_server/Camera/userland/containers/raw /home/pi/git_server/Camera/userland/build/raspberry/release /home/pi/git_server/Camera/userland/build/raspberry/release/containers/raw /home/pi/git_server/Camera/userland/build/raspberry/release/containers/raw/CMakeFiles/writer_raw_video.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : containers/raw/CMakeFiles/writer_raw_video.dir/depend

