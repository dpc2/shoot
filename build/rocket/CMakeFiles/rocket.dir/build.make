# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/x/workspace/shoot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/x/workspace/shoot/build

# Include any dependencies generated for this target.
include rocket/CMakeFiles/rocket.dir/depend.make

# Include the progress variables for this target.
include rocket/CMakeFiles/rocket.dir/progress.make

# Include the compile flags for this target's objects.
include rocket/CMakeFiles/rocket.dir/flags.make

rocket/CMakeFiles/rocket.dir/bomb.cpp.o: rocket/CMakeFiles/rocket.dir/flags.make
rocket/CMakeFiles/rocket.dir/bomb.cpp.o: ../rocket/bomb.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/x/workspace/shoot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object rocket/CMakeFiles/rocket.dir/bomb.cpp.o"
	cd /home/x/workspace/shoot/build/rocket && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rocket.dir/bomb.cpp.o -c /home/x/workspace/shoot/rocket/bomb.cpp

rocket/CMakeFiles/rocket.dir/bomb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rocket.dir/bomb.cpp.i"
	cd /home/x/workspace/shoot/build/rocket && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/x/workspace/shoot/rocket/bomb.cpp > CMakeFiles/rocket.dir/bomb.cpp.i

rocket/CMakeFiles/rocket.dir/bomb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rocket.dir/bomb.cpp.s"
	cd /home/x/workspace/shoot/build/rocket && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/x/workspace/shoot/rocket/bomb.cpp -o CMakeFiles/rocket.dir/bomb.cpp.s

rocket/CMakeFiles/rocket.dir/particle.cpp.o: rocket/CMakeFiles/rocket.dir/flags.make
rocket/CMakeFiles/rocket.dir/particle.cpp.o: ../rocket/particle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/x/workspace/shoot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object rocket/CMakeFiles/rocket.dir/particle.cpp.o"
	cd /home/x/workspace/shoot/build/rocket && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rocket.dir/particle.cpp.o -c /home/x/workspace/shoot/rocket/particle.cpp

rocket/CMakeFiles/rocket.dir/particle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rocket.dir/particle.cpp.i"
	cd /home/x/workspace/shoot/build/rocket && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/x/workspace/shoot/rocket/particle.cpp > CMakeFiles/rocket.dir/particle.cpp.i

rocket/CMakeFiles/rocket.dir/particle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rocket.dir/particle.cpp.s"
	cd /home/x/workspace/shoot/build/rocket && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/x/workspace/shoot/rocket/particle.cpp -o CMakeFiles/rocket.dir/particle.cpp.s

rocket/CMakeFiles/rocket.dir/rocket.cpp.o: rocket/CMakeFiles/rocket.dir/flags.make
rocket/CMakeFiles/rocket.dir/rocket.cpp.o: ../rocket/rocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/x/workspace/shoot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object rocket/CMakeFiles/rocket.dir/rocket.cpp.o"
	cd /home/x/workspace/shoot/build/rocket && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rocket.dir/rocket.cpp.o -c /home/x/workspace/shoot/rocket/rocket.cpp

rocket/CMakeFiles/rocket.dir/rocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rocket.dir/rocket.cpp.i"
	cd /home/x/workspace/shoot/build/rocket && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/x/workspace/shoot/rocket/rocket.cpp > CMakeFiles/rocket.dir/rocket.cpp.i

rocket/CMakeFiles/rocket.dir/rocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rocket.dir/rocket.cpp.s"
	cd /home/x/workspace/shoot/build/rocket && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/x/workspace/shoot/rocket/rocket.cpp -o CMakeFiles/rocket.dir/rocket.cpp.s

rocket/CMakeFiles/rocket.dir/rocket2.cpp.o: rocket/CMakeFiles/rocket.dir/flags.make
rocket/CMakeFiles/rocket.dir/rocket2.cpp.o: ../rocket/rocket2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/x/workspace/shoot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object rocket/CMakeFiles/rocket.dir/rocket2.cpp.o"
	cd /home/x/workspace/shoot/build/rocket && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rocket.dir/rocket2.cpp.o -c /home/x/workspace/shoot/rocket/rocket2.cpp

rocket/CMakeFiles/rocket.dir/rocket2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rocket.dir/rocket2.cpp.i"
	cd /home/x/workspace/shoot/build/rocket && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/x/workspace/shoot/rocket/rocket2.cpp > CMakeFiles/rocket.dir/rocket2.cpp.i

rocket/CMakeFiles/rocket.dir/rocket2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rocket.dir/rocket2.cpp.s"
	cd /home/x/workspace/shoot/build/rocket && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/x/workspace/shoot/rocket/rocket2.cpp -o CMakeFiles/rocket.dir/rocket2.cpp.s

# Object files for target rocket
rocket_OBJECTS = \
"CMakeFiles/rocket.dir/bomb.cpp.o" \
"CMakeFiles/rocket.dir/particle.cpp.o" \
"CMakeFiles/rocket.dir/rocket.cpp.o" \
"CMakeFiles/rocket.dir/rocket2.cpp.o"

# External object files for target rocket
rocket_EXTERNAL_OBJECTS =

rocket/librocket.a: rocket/CMakeFiles/rocket.dir/bomb.cpp.o
rocket/librocket.a: rocket/CMakeFiles/rocket.dir/particle.cpp.o
rocket/librocket.a: rocket/CMakeFiles/rocket.dir/rocket.cpp.o
rocket/librocket.a: rocket/CMakeFiles/rocket.dir/rocket2.cpp.o
rocket/librocket.a: rocket/CMakeFiles/rocket.dir/build.make
rocket/librocket.a: rocket/CMakeFiles/rocket.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/x/workspace/shoot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library librocket.a"
	cd /home/x/workspace/shoot/build/rocket && $(CMAKE_COMMAND) -P CMakeFiles/rocket.dir/cmake_clean_target.cmake
	cd /home/x/workspace/shoot/build/rocket && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rocket.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
rocket/CMakeFiles/rocket.dir/build: rocket/librocket.a

.PHONY : rocket/CMakeFiles/rocket.dir/build

rocket/CMakeFiles/rocket.dir/clean:
	cd /home/x/workspace/shoot/build/rocket && $(CMAKE_COMMAND) -P CMakeFiles/rocket.dir/cmake_clean.cmake
.PHONY : rocket/CMakeFiles/rocket.dir/clean

rocket/CMakeFiles/rocket.dir/depend:
	cd /home/x/workspace/shoot/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/x/workspace/shoot /home/x/workspace/shoot/rocket /home/x/workspace/shoot/build /home/x/workspace/shoot/build/rocket /home/x/workspace/shoot/build/rocket/CMakeFiles/rocket.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : rocket/CMakeFiles/rocket.dir/depend

