# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /opt/clion-2019.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.2.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nuka/CLionProjects/CourseCpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nuka/CLionProjects/CourseCpp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CourseCpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CourseCpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CourseCpp.dir/flags.make

CMakeFiles/CourseCpp.dir/main.cpp.o: CMakeFiles/CourseCpp.dir/flags.make
CMakeFiles/CourseCpp.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nuka/CLionProjects/CourseCpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CourseCpp.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CourseCpp.dir/main.cpp.o -c /home/nuka/CLionProjects/CourseCpp/main.cpp

CMakeFiles/CourseCpp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CourseCpp.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nuka/CLionProjects/CourseCpp/main.cpp > CMakeFiles/CourseCpp.dir/main.cpp.i

CMakeFiles/CourseCpp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CourseCpp.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nuka/CLionProjects/CourseCpp/main.cpp -o CMakeFiles/CourseCpp.dir/main.cpp.s

CMakeFiles/CourseCpp.dir/bmp.cpp.o: CMakeFiles/CourseCpp.dir/flags.make
CMakeFiles/CourseCpp.dir/bmp.cpp.o: ../bmp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nuka/CLionProjects/CourseCpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CourseCpp.dir/bmp.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CourseCpp.dir/bmp.cpp.o -c /home/nuka/CLionProjects/CourseCpp/bmp.cpp

CMakeFiles/CourseCpp.dir/bmp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CourseCpp.dir/bmp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nuka/CLionProjects/CourseCpp/bmp.cpp > CMakeFiles/CourseCpp.dir/bmp.cpp.i

CMakeFiles/CourseCpp.dir/bmp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CourseCpp.dir/bmp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nuka/CLionProjects/CourseCpp/bmp.cpp -o CMakeFiles/CourseCpp.dir/bmp.cpp.s

# Object files for target CourseCpp
CourseCpp_OBJECTS = \
"CMakeFiles/CourseCpp.dir/main.cpp.o" \
"CMakeFiles/CourseCpp.dir/bmp.cpp.o"

# External object files for target CourseCpp
CourseCpp_EXTERNAL_OBJECTS =

CourseCpp: CMakeFiles/CourseCpp.dir/main.cpp.o
CourseCpp: CMakeFiles/CourseCpp.dir/bmp.cpp.o
CourseCpp: CMakeFiles/CourseCpp.dir/build.make
CourseCpp: CMakeFiles/CourseCpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nuka/CLionProjects/CourseCpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable CourseCpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CourseCpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CourseCpp.dir/build: CourseCpp

.PHONY : CMakeFiles/CourseCpp.dir/build

CMakeFiles/CourseCpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CourseCpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CourseCpp.dir/clean

CMakeFiles/CourseCpp.dir/depend:
	cd /home/nuka/CLionProjects/CourseCpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nuka/CLionProjects/CourseCpp /home/nuka/CLionProjects/CourseCpp /home/nuka/CLionProjects/CourseCpp/cmake-build-debug /home/nuka/CLionProjects/CourseCpp/cmake-build-debug /home/nuka/CLionProjects/CourseCpp/cmake-build-debug/CMakeFiles/CourseCpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CourseCpp.dir/depend
