# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\polyethylene\Github\myLispInterpreter\source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\polyethylene\Github\myLispInterpreter\source\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/source.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/source.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/source.dir/flags.make

CMakeFiles/source.dir/main.c.obj: CMakeFiles/source.dir/flags.make
CMakeFiles/source.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\polyethylene\Github\myLispInterpreter\source\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/source.dir/main.c.obj"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\source.dir\main.c.obj   -c C:\polyethylene\Github\myLispInterpreter\source\main.c

CMakeFiles/source.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/source.dir/main.c.i"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\polyethylene\Github\myLispInterpreter\source\main.c > CMakeFiles\source.dir\main.c.i

CMakeFiles/source.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/source.dir/main.c.s"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\polyethylene\Github\myLispInterpreter\source\main.c -o CMakeFiles\source.dir\main.c.s

CMakeFiles/source.dir/mpc.c.obj: CMakeFiles/source.dir/flags.make
CMakeFiles/source.dir/mpc.c.obj: ../mpc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\polyethylene\Github\myLispInterpreter\source\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/source.dir/mpc.c.obj"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\source.dir\mpc.c.obj   -c C:\polyethylene\Github\myLispInterpreter\source\mpc.c

CMakeFiles/source.dir/mpc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/source.dir/mpc.c.i"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\polyethylene\Github\myLispInterpreter\source\mpc.c > CMakeFiles\source.dir\mpc.c.i

CMakeFiles/source.dir/mpc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/source.dir/mpc.c.s"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\polyethylene\Github\myLispInterpreter\source\mpc.c -o CMakeFiles\source.dir\mpc.c.s

CMakeFiles/source.dir/read.c.obj: CMakeFiles/source.dir/flags.make
CMakeFiles/source.dir/read.c.obj: ../read.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\polyethylene\Github\myLispInterpreter\source\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/source.dir/read.c.obj"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\source.dir\read.c.obj   -c C:\polyethylene\Github\myLispInterpreter\source\read.c

CMakeFiles/source.dir/read.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/source.dir/read.c.i"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\polyethylene\Github\myLispInterpreter\source\read.c > CMakeFiles\source.dir\read.c.i

CMakeFiles/source.dir/read.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/source.dir/read.c.s"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\polyethylene\Github\myLispInterpreter\source\read.c -o CMakeFiles\source.dir\read.c.s

CMakeFiles/source.dir/value_type.c.obj: CMakeFiles/source.dir/flags.make
CMakeFiles/source.dir/value_type.c.obj: ../value_type.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\polyethylene\Github\myLispInterpreter\source\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/source.dir/value_type.c.obj"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\source.dir\value_type.c.obj   -c C:\polyethylene\Github\myLispInterpreter\source\value_type.c

CMakeFiles/source.dir/value_type.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/source.dir/value_type.c.i"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\polyethylene\Github\myLispInterpreter\source\value_type.c > CMakeFiles\source.dir\value_type.c.i

CMakeFiles/source.dir/value_type.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/source.dir/value_type.c.s"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\polyethylene\Github\myLispInterpreter\source\value_type.c -o CMakeFiles\source.dir\value_type.c.s

CMakeFiles/source.dir/eval.c.obj: CMakeFiles/source.dir/flags.make
CMakeFiles/source.dir/eval.c.obj: ../eval.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\polyethylene\Github\myLispInterpreter\source\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/source.dir/eval.c.obj"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\source.dir\eval.c.obj   -c C:\polyethylene\Github\myLispInterpreter\source\eval.c

CMakeFiles/source.dir/eval.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/source.dir/eval.c.i"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\polyethylene\Github\myLispInterpreter\source\eval.c > CMakeFiles\source.dir\eval.c.i

CMakeFiles/source.dir/eval.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/source.dir/eval.c.s"
	C:\PROGRA~2\TDM-GCC\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\polyethylene\Github\myLispInterpreter\source\eval.c -o CMakeFiles\source.dir\eval.c.s

# Object files for target source
source_OBJECTS = \
"CMakeFiles/source.dir/main.c.obj" \
"CMakeFiles/source.dir/mpc.c.obj" \
"CMakeFiles/source.dir/read.c.obj" \
"CMakeFiles/source.dir/value_type.c.obj" \
"CMakeFiles/source.dir/eval.c.obj"

# External object files for target source
source_EXTERNAL_OBJECTS =

source.exe: CMakeFiles/source.dir/main.c.obj
source.exe: CMakeFiles/source.dir/mpc.c.obj
source.exe: CMakeFiles/source.dir/read.c.obj
source.exe: CMakeFiles/source.dir/value_type.c.obj
source.exe: CMakeFiles/source.dir/eval.c.obj
source.exe: CMakeFiles/source.dir/build.make
source.exe: CMakeFiles/source.dir/linklibs.rsp
source.exe: CMakeFiles/source.dir/objects1.rsp
source.exe: CMakeFiles/source.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\polyethylene\Github\myLispInterpreter\source\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable source.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\source.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/source.dir/build: source.exe

.PHONY : CMakeFiles/source.dir/build

CMakeFiles/source.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\source.dir\cmake_clean.cmake
.PHONY : CMakeFiles/source.dir/clean

CMakeFiles/source.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\polyethylene\Github\myLispInterpreter\source C:\polyethylene\Github\myLispInterpreter\source C:\polyethylene\Github\myLispInterpreter\source\cmake-build-debug C:\polyethylene\Github\myLispInterpreter\source\cmake-build-debug C:\polyethylene\Github\myLispInterpreter\source\cmake-build-debug\CMakeFiles\source.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/source.dir/depend

