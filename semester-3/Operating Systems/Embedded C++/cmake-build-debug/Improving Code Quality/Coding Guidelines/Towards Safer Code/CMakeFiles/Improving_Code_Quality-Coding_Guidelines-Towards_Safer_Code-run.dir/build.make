# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /home/marling/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/marling/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/cmake-build-debug"

# Include any dependencies generated for this target.
include Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/compiler_depend.make

# Include the progress variables for this target.
include Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/progress.make

# Include the compile flags for this target's objects.
include Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/flags.make

Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.o: Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/flags.make
Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.o: /home/marling/Documents/college-CS/semester-3/Operating\ Systems/Embedded\ C++/Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/src/main.cpp
Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.o: Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Improving Code Quality/Coding Guidelines/Towards Safer Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.o"
	cd "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/cmake-build-debug/Improving Code Quality/Coding Guidelines/Towards Safer Code" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT "Improving\\ Code\\ Quality/Coding\\ Guidelines/Towards\\ Safer\\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.o" -MF CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.o.d -o CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.o -c "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/Improving Code Quality/Coding Guidelines/Towards Safer Code/src/main.cpp"

Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.i"
	cd "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/cmake-build-debug/Improving Code Quality/Coding Guidelines/Towards Safer Code" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/Improving Code Quality/Coding Guidelines/Towards Safer Code/src/main.cpp" > CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.i

Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.s"
	cd "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/cmake-build-debug/Improving Code Quality/Coding Guidelines/Towards Safer Code" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/Improving Code Quality/Coding Guidelines/Towards Safer Code/src/main.cpp" -o CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.s

# Object files for target Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run
Improving_Code_Quality__Coding_Guidelines__Towards_Safer_Code__run_OBJECTS = \
"CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.o"

# External object files for target Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run
Improving_Code_Quality__Coding_Guidelines__Towards_Safer_Code__run_EXTERNAL_OBJECTS =

Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run: Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/src/main.cpp.o
Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run: Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/build.make
Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run: Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run"
	cd "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/cmake-build-debug/Improving Code Quality/Coding Guidelines/Towards Safer Code" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/build: Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run
.PHONY : Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/build

Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/clean:
	cd "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/cmake-build-debug/Improving Code Quality/Coding Guidelines/Towards Safer Code" && $(CMAKE_COMMAND) -P CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/cmake_clean.cmake
.PHONY : Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/clean

Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/depend:
	cd "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++" "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/Improving Code Quality/Coding Guidelines/Towards Safer Code" "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/cmake-build-debug" "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/cmake-build-debug/Improving Code Quality/Coding Guidelines/Towards Safer Code" "/home/marling/Documents/college-CS/semester-3/Operating Systems/Embedded C++/cmake-build-debug/Improving Code Quality/Coding Guidelines/Towards Safer Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : Improving\ Code\ Quality/Coding\ Guidelines/Towards\ Safer\ Code/CMakeFiles/Improving_Code_Quality-Coding_Guidelines-Towards_Safer_Code-run.dir/depend
