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
include dep/glfw/examples/CMakeFiles/boing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dep/glfw/examples/CMakeFiles/boing.dir/compiler_depend.make

# Include the progress variables for this target.
include dep/glfw/examples/CMakeFiles/boing.dir/progress.make

# Include the compile flags for this target's objects.
include dep/glfw/examples/CMakeFiles/boing.dir/flags.make

dep/glfw/examples/CMakeFiles/boing.dir/boing.c.o: dep/glfw/examples/CMakeFiles/boing.dir/flags.make
dep/glfw/examples/CMakeFiles/boing.dir/boing.c.o: dep/glfw/examples/boing.c
dep/glfw/examples/CMakeFiles/boing.dir/boing.c.o: dep/glfw/examples/CMakeFiles/boing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/mrbigoudi/Documents/M1/IGR200/TP3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dep/glfw/examples/CMakeFiles/boing.dir/boing.c.o"
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dep/glfw/examples/CMakeFiles/boing.dir/boing.c.o -MF CMakeFiles/boing.dir/boing.c.o.d -o CMakeFiles/boing.dir/boing.c.o -c /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples/boing.c

dep/glfw/examples/CMakeFiles/boing.dir/boing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/boing.dir/boing.c.i"
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples/boing.c > CMakeFiles/boing.dir/boing.c.i

dep/glfw/examples/CMakeFiles/boing.dir/boing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/boing.dir/boing.c.s"
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples/boing.c -o CMakeFiles/boing.dir/boing.c.s

dep/glfw/examples/CMakeFiles/boing.dir/__/deps/glad_gl.c.o: dep/glfw/examples/CMakeFiles/boing.dir/flags.make
dep/glfw/examples/CMakeFiles/boing.dir/__/deps/glad_gl.c.o: dep/glfw/deps/glad_gl.c
dep/glfw/examples/CMakeFiles/boing.dir/__/deps/glad_gl.c.o: dep/glfw/examples/CMakeFiles/boing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/mrbigoudi/Documents/M1/IGR200/TP3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object dep/glfw/examples/CMakeFiles/boing.dir/__/deps/glad_gl.c.o"
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dep/glfw/examples/CMakeFiles/boing.dir/__/deps/glad_gl.c.o -MF CMakeFiles/boing.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/boing.dir/__/deps/glad_gl.c.o -c /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/deps/glad_gl.c

dep/glfw/examples/CMakeFiles/boing.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/boing.dir/__/deps/glad_gl.c.i"
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/deps/glad_gl.c > CMakeFiles/boing.dir/__/deps/glad_gl.c.i

dep/glfw/examples/CMakeFiles/boing.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/boing.dir/__/deps/glad_gl.c.s"
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/deps/glad_gl.c -o CMakeFiles/boing.dir/__/deps/glad_gl.c.s

# Object files for target boing
boing_OBJECTS = \
"CMakeFiles/boing.dir/boing.c.o" \
"CMakeFiles/boing.dir/__/deps/glad_gl.c.o"

# External object files for target boing
boing_EXTERNAL_OBJECTS =

dep/glfw/examples/boing: dep/glfw/examples/CMakeFiles/boing.dir/boing.c.o
dep/glfw/examples/boing: dep/glfw/examples/CMakeFiles/boing.dir/__/deps/glad_gl.c.o
dep/glfw/examples/boing: dep/glfw/examples/CMakeFiles/boing.dir/build.make
dep/glfw/examples/boing: dep/glfw/src/libglfw3.a
dep/glfw/examples/boing: /usr/lib/libm.so
dep/glfw/examples/boing: /usr/lib/librt.a
dep/glfw/examples/boing: /usr/lib/libm.so
dep/glfw/examples/boing: /usr/lib/libX11.so
dep/glfw/examples/boing: dep/glfw/examples/CMakeFiles/boing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/mrbigoudi/Documents/M1/IGR200/TP3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable boing"
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/boing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dep/glfw/examples/CMakeFiles/boing.dir/build: dep/glfw/examples/boing
.PHONY : dep/glfw/examples/CMakeFiles/boing.dir/build

dep/glfw/examples/CMakeFiles/boing.dir/clean:
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples && $(CMAKE_COMMAND) -P CMakeFiles/boing.dir/cmake_clean.cmake
.PHONY : dep/glfw/examples/CMakeFiles/boing.dir/clean

dep/glfw/examples/CMakeFiles/boing.dir/depend:
	cd /home/mrbigoudi/Documents/M1/IGR200/TP3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mrbigoudi/Documents/M1/IGR200/TP3 /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples /home/mrbigoudi/Documents/M1/IGR200/TP3 /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples /home/mrbigoudi/Documents/M1/IGR200/TP3/dep/glfw/examples/CMakeFiles/boing.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dep/glfw/examples/CMakeFiles/boing.dir/depend

