# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kilso/Documents/CProjects/OwnText

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kilso/Documents/CProjects/OwnText/build

# Include any dependencies generated for this target.
include CMakeFiles/OwnText.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OwnText.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OwnText.dir/flags.make

CMakeFiles/OwnText.dir/src/args.c.o: CMakeFiles/OwnText.dir/flags.make
CMakeFiles/OwnText.dir/src/args.c.o: ../src/args.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kilso/Documents/CProjects/OwnText/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/OwnText.dir/src/args.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OwnText.dir/src/args.c.o   -c /home/kilso/Documents/CProjects/OwnText/src/args.c

CMakeFiles/OwnText.dir/src/args.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OwnText.dir/src/args.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kilso/Documents/CProjects/OwnText/src/args.c > CMakeFiles/OwnText.dir/src/args.c.i

CMakeFiles/OwnText.dir/src/args.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OwnText.dir/src/args.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kilso/Documents/CProjects/OwnText/src/args.c -o CMakeFiles/OwnText.dir/src/args.c.s

CMakeFiles/OwnText.dir/src/logging.c.o: CMakeFiles/OwnText.dir/flags.make
CMakeFiles/OwnText.dir/src/logging.c.o: ../src/logging.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kilso/Documents/CProjects/OwnText/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/OwnText.dir/src/logging.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OwnText.dir/src/logging.c.o   -c /home/kilso/Documents/CProjects/OwnText/src/logging.c

CMakeFiles/OwnText.dir/src/logging.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OwnText.dir/src/logging.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kilso/Documents/CProjects/OwnText/src/logging.c > CMakeFiles/OwnText.dir/src/logging.c.i

CMakeFiles/OwnText.dir/src/logging.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OwnText.dir/src/logging.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kilso/Documents/CProjects/OwnText/src/logging.c -o CMakeFiles/OwnText.dir/src/logging.c.s

CMakeFiles/OwnText.dir/src/owntext.c.o: CMakeFiles/OwnText.dir/flags.make
CMakeFiles/OwnText.dir/src/owntext.c.o: ../src/owntext.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kilso/Documents/CProjects/OwnText/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/OwnText.dir/src/owntext.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OwnText.dir/src/owntext.c.o   -c /home/kilso/Documents/CProjects/OwnText/src/owntext.c

CMakeFiles/OwnText.dir/src/owntext.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OwnText.dir/src/owntext.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kilso/Documents/CProjects/OwnText/src/owntext.c > CMakeFiles/OwnText.dir/src/owntext.c.i

CMakeFiles/OwnText.dir/src/owntext.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OwnText.dir/src/owntext.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kilso/Documents/CProjects/OwnText/src/owntext.c -o CMakeFiles/OwnText.dir/src/owntext.c.s

CMakeFiles/OwnText.dir/src/termio.c.o: CMakeFiles/OwnText.dir/flags.make
CMakeFiles/OwnText.dir/src/termio.c.o: ../src/termio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kilso/Documents/CProjects/OwnText/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/OwnText.dir/src/termio.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OwnText.dir/src/termio.c.o   -c /home/kilso/Documents/CProjects/OwnText/src/termio.c

CMakeFiles/OwnText.dir/src/termio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OwnText.dir/src/termio.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kilso/Documents/CProjects/OwnText/src/termio.c > CMakeFiles/OwnText.dir/src/termio.c.i

CMakeFiles/OwnText.dir/src/termio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OwnText.dir/src/termio.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kilso/Documents/CProjects/OwnText/src/termio.c -o CMakeFiles/OwnText.dir/src/termio.c.s

CMakeFiles/OwnText.dir/src/window.c.o: CMakeFiles/OwnText.dir/flags.make
CMakeFiles/OwnText.dir/src/window.c.o: ../src/window.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kilso/Documents/CProjects/OwnText/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/OwnText.dir/src/window.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OwnText.dir/src/window.c.o   -c /home/kilso/Documents/CProjects/OwnText/src/window.c

CMakeFiles/OwnText.dir/src/window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OwnText.dir/src/window.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kilso/Documents/CProjects/OwnText/src/window.c > CMakeFiles/OwnText.dir/src/window.c.i

CMakeFiles/OwnText.dir/src/window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OwnText.dir/src/window.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kilso/Documents/CProjects/OwnText/src/window.c -o CMakeFiles/OwnText.dir/src/window.c.s

# Object files for target OwnText
OwnText_OBJECTS = \
"CMakeFiles/OwnText.dir/src/args.c.o" \
"CMakeFiles/OwnText.dir/src/logging.c.o" \
"CMakeFiles/OwnText.dir/src/owntext.c.o" \
"CMakeFiles/OwnText.dir/src/termio.c.o" \
"CMakeFiles/OwnText.dir/src/window.c.o"

# External object files for target OwnText
OwnText_EXTERNAL_OBJECTS =

OwnText: CMakeFiles/OwnText.dir/src/args.c.o
OwnText: CMakeFiles/OwnText.dir/src/logging.c.o
OwnText: CMakeFiles/OwnText.dir/src/owntext.c.o
OwnText: CMakeFiles/OwnText.dir/src/termio.c.o
OwnText: CMakeFiles/OwnText.dir/src/window.c.o
OwnText: CMakeFiles/OwnText.dir/build.make
OwnText: CMakeFiles/OwnText.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kilso/Documents/CProjects/OwnText/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable OwnText"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OwnText.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OwnText.dir/build: OwnText

.PHONY : CMakeFiles/OwnText.dir/build

CMakeFiles/OwnText.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OwnText.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OwnText.dir/clean

CMakeFiles/OwnText.dir/depend:
	cd /home/kilso/Documents/CProjects/OwnText/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kilso/Documents/CProjects/OwnText /home/kilso/Documents/CProjects/OwnText /home/kilso/Documents/CProjects/OwnText/build /home/kilso/Documents/CProjects/OwnText/build /home/kilso/Documents/CProjects/OwnText/build/CMakeFiles/OwnText.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OwnText.dir/depend
