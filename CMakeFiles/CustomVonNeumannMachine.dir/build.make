# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/joaop/TP_02-SO/CustomVonNeumannMachine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joaop/TP_02-SO/CustomVonNeumannMachine

# Include any dependencies generated for this target.
include CMakeFiles/CustomVonNeumannMachine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CustomVonNeumannMachine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CustomVonNeumannMachine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CustomVonNeumannMachine.dir/flags.make

CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/flags.make
CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaop/TP_02-SO/CustomVonNeumannMachine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.o -MF CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.o.d -o CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.o -c /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/main.cpp

CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/main.cpp > CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.i

CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/main.cpp -o CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.s

CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/flags.make
CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.o: src/loader.cpp
CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaop/TP_02-SO/CustomVonNeumannMachine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.o -MF CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.o.d -o CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.o -c /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/loader.cpp

CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/loader.cpp > CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.i

CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/loader.cpp -o CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.s

CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/flags.make
CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.o: src/cpu/CONTROL_UNIT.cpp
CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaop/TP_02-SO/CustomVonNeumannMachine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.o -MF CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.o.d -o CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.o -c /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/cpu/CONTROL_UNIT.cpp

CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/cpu/CONTROL_UNIT.cpp > CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.i

CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/cpu/CONTROL_UNIT.cpp -o CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.s

CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/flags.make
CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.o: src/cpu/REGISTER.cpp
CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaop/TP_02-SO/CustomVonNeumannMachine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.o -MF CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.o.d -o CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.o -c /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/cpu/REGISTER.cpp

CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/cpu/REGISTER.cpp > CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.i

CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/cpu/REGISTER.cpp -o CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.s

CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/flags.make
CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.o: src/cpu/REGISTER_BANK.cpp
CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaop/TP_02-SO/CustomVonNeumannMachine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.o -MF CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.o.d -o CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.o -c /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/cpu/REGISTER_BANK.cpp

CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/cpu/REGISTER_BANK.cpp > CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.i

CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/cpu/REGISTER_BANK.cpp -o CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.s

CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/flags.make
CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.o: src/cpu/ALU.cpp
CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaop/TP_02-SO/CustomVonNeumannMachine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.o -MF CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.o.d -o CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.o -c /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/cpu/ALU.cpp

CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/cpu/ALU.cpp > CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.i

CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/cpu/ALU.cpp -o CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.s

CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/flags.make
CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.o: src/memory/MEMORYCELL.cpp
CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaop/TP_02-SO/CustomVonNeumannMachine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.o -MF CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.o.d -o CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.o -c /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/memory/MEMORYCELL.cpp

CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/memory/MEMORYCELL.cpp > CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.i

CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/memory/MEMORYCELL.cpp -o CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.s

CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/flags.make
CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.o: src/memory/MAINMEMORY.cpp
CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaop/TP_02-SO/CustomVonNeumannMachine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.o -MF CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.o.d -o CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.o -c /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/memory/MAINMEMORY.cpp

CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/memory/MAINMEMORY.cpp > CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.i

CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/memory/MAINMEMORY.cpp -o CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.s

CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/flags.make
CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.o: src/memory/CACHE.cpp
CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.o: CMakeFiles/CustomVonNeumannMachine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaop/TP_02-SO/CustomVonNeumannMachine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.o -MF CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.o.d -o CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.o -c /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/memory/CACHE.cpp

CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/memory/CACHE.cpp > CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.i

CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaop/TP_02-SO/CustomVonNeumannMachine/src/memory/CACHE.cpp -o CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.s

# Object files for target CustomVonNeumannMachine
CustomVonNeumannMachine_OBJECTS = \
"CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.o" \
"CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.o" \
"CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.o" \
"CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.o" \
"CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.o" \
"CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.o" \
"CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.o" \
"CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.o" \
"CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.o"

# External object files for target CustomVonNeumannMachine
CustomVonNeumannMachine_EXTERNAL_OBJECTS =

CustomVonNeumannMachine: CMakeFiles/CustomVonNeumannMachine.dir/src/main.cpp.o
CustomVonNeumannMachine: CMakeFiles/CustomVonNeumannMachine.dir/src/loader.cpp.o
CustomVonNeumannMachine: CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/CONTROL_UNIT.cpp.o
CustomVonNeumannMachine: CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER.cpp.o
CustomVonNeumannMachine: CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/REGISTER_BANK.cpp.o
CustomVonNeumannMachine: CMakeFiles/CustomVonNeumannMachine.dir/src/cpu/ALU.cpp.o
CustomVonNeumannMachine: CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MEMORYCELL.cpp.o
CustomVonNeumannMachine: CMakeFiles/CustomVonNeumannMachine.dir/src/memory/MAINMEMORY.cpp.o
CustomVonNeumannMachine: CMakeFiles/CustomVonNeumannMachine.dir/src/memory/CACHE.cpp.o
CustomVonNeumannMachine: CMakeFiles/CustomVonNeumannMachine.dir/build.make
CustomVonNeumannMachine: CMakeFiles/CustomVonNeumannMachine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joaop/TP_02-SO/CustomVonNeumannMachine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable CustomVonNeumannMachine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CustomVonNeumannMachine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CustomVonNeumannMachine.dir/build: CustomVonNeumannMachine
.PHONY : CMakeFiles/CustomVonNeumannMachine.dir/build

CMakeFiles/CustomVonNeumannMachine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CustomVonNeumannMachine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CustomVonNeumannMachine.dir/clean

CMakeFiles/CustomVonNeumannMachine.dir/depend:
	cd /home/joaop/TP_02-SO/CustomVonNeumannMachine && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joaop/TP_02-SO/CustomVonNeumannMachine /home/joaop/TP_02-SO/CustomVonNeumannMachine /home/joaop/TP_02-SO/CustomVonNeumannMachine /home/joaop/TP_02-SO/CustomVonNeumannMachine /home/joaop/TP_02-SO/CustomVonNeumannMachine/CMakeFiles/CustomVonNeumannMachine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CustomVonNeumannMachine.dir/depend

