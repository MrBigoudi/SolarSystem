# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mrbigoudi/Documents/M1/IGR200/TP3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mrbigoudi/Documents/M1/IGR200/TP3

# Include any dependencies generated for this target.
include dep/glfw/examples/CMakeFiles/sharing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dep/glfw/examples/CMakeFiles/sharing.dir/compiler_depend.make

# Include the progress variables for this target.
include dep/glfw/examples/CMakeFiles/sharing.dir/progress.make

# Include the compile flags for this target's objects.
include dep/glfw/examples/CMakeFiles/sharing.dir/flags.make

dep/glfw/examples/CMakeFiles/sharing.dir/sharing.c.o: dep/glfw/examples/CMakeFiles/sharing.dir/flags.make
dep/glfw/examples/CMakeFiles/sharing.dir/sharing.c.o: dep/glfw/examples/sharing.c
dep/glfw/examples/CMakeFiles/sharing.dir/sharing.c.o: dep/glfw/examples/CMakeFiles/sharing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/mrbigoudi/Documents/M1/IGR200/TP3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dep/glfw/examples/CMakeFiles/sharing.dir/sharing.c.o"
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dep/glfw/examples/CMakeFiles/sharing.dir/sharing.c.o -MF CMakeFiles/sharing.dir/sharing.c.o.d -o CMakeFiles/sharing.dir/sharing.c.o -c /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples/sharing.c

dep/glfw/examples/CMakeFiles/sharing.dir/sharing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/sharing.dir/sharing.c.i"
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples/sharing.c > CMakeFiles/sharing.dir/sharing.c.i

dep/glfw/examples/CMakeFiles/sharing.dir/sharing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/sharing.dir/sharing.c.s"
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples/sharing.c -o CMakeFiles/sharing.dir/sharing.c.s

dep/glfw/examples/CMakeFiles/sharing.dir/__/deps/glad_gl.c.o: dep/glfw/examples/CMakeFiles/sharing.dir/flags.make
dep/glfw/examples/CMakeFiles/sharing.dir/__/deps/glad_gl.c.o: dep/glfw/deps/glad_gl.c
dep/glfw/examples/CMakeFiles/sharing.dir/__/deps/glad_gl.c.o: dep/glfw/examples/CMakeFiles/sharing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/mrbigoudi/Documents/M1/IGR200/TP3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object dep/glfw/examples/CMakeFiles/sharing.dir/__/deps/glad_gl.c.o"
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dep/glfw/examples/CMakeFiles/sharing.dir/__/deps/glad_gl.c.o -MF CMakeFiles/sharing.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/sharing.dir/__/deps/glad_gl.c.o -c /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/deps/glad_gl.c

dep/glfw/examples/CMakeFiles/sharing.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/sharing.dir/__/deps/glad_gl.c.i"
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/deps/glad_gl.c > CMakeFiles/sharing.dir/__/deps/glad_gl.c.i

dep/glfw/examples/CMakeFiles/sharing.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/sharing.dir/__/deps/glad_gl.c.s"
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/deps/glad_gl.c -o CMakeFiles/sharing.dir/__/deps/glad_gl.c.s

# Object files for target sharing
sharing_OBJECTS = \
"CMakeFiles/sharing.dir/sharing.c.o" \
"CMakeFiles/sharing.dir/__/deps/glad_gl.c.o"

# External object files for target sharing
sharing_EXTERNAL_OBJECTS =

build/sharing: dep/glfw/examples/CMakeFiles/sharing.dir/sharing.c.o
build/sharing: dep/glfw/examples/CMakeFiles/sharing.dir/__/deps/glad_gl.c.o
build/sharing: dep/glfw/examples/CMakeFiles/sharing.dir/build.make
build/sharing: dep/glfw/src/libglfw3.a
build/sharing: /usr/lib/libm.so
build/sharing: /usr/lib/librt.a
build/sharing: /usr/lib/libm.so
build/sharing: /usr/lib/libX11.so
build/sharing: dep/glfw/examples/CMakeFiles/sharing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/mrbigoudi/Documents/M1/IGR200/TP3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ../../../build/sharing"
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sharing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dep/glfw/examples/CMakeFiles/sharing.dir/build: build/sharing
.PHONY : dep/glfw/examples/CMakeFiles/sharing.dir/build

dep/glfw/examples/CMakeFiles/sharing.dir/clean:
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && $(CMAKE_COMMAND) -P CMakeFiles/sharing.dir/cmake_clean.cmake
.PHONY : dep/glfw/examples/CMakeFiles/sharing.dir/clean

dep/glfw/examples/CMakeFiles/sharing.dir/depend:
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mrbigoudi/Documents/M1/IGR200/TP3 /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples /home/mrbigoudi/Documents/M1/IGR200/TP3 /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples/CMakeFiles/sharing.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dep/glfw/examples/CMakeFiles/sharing.dir/depend

