# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.3.1\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.3.1\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\VH\CLionProjects\Section2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\VH\CLionProjects\Section2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Section2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Section2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Section2.dir/flags.make

CMakeFiles/Section2.dir/PartA.c.obj: CMakeFiles/Section2.dir/flags.make
CMakeFiles/Section2.dir/PartA.c.obj: ../PartA.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\VH\CLionProjects\Section2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Section2.dir/PartA.c.obj"
	C:\PROGRA~2\mingw-w64\i686-7.2.0-posix-dwarf-rt_v5-rev1\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Section2.dir\PartA.c.obj   -c C:\Users\VH\CLionProjects\Section2\PartA.c

CMakeFiles/Section2.dir/PartA.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Section2.dir/PartA.c.i"
	C:\PROGRA~2\mingw-w64\i686-7.2.0-posix-dwarf-rt_v5-rev1\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\VH\CLionProjects\Section2\PartA.c > CMakeFiles\Section2.dir\PartA.c.i

CMakeFiles/Section2.dir/PartA.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Section2.dir/PartA.c.s"
	C:\PROGRA~2\mingw-w64\i686-7.2.0-posix-dwarf-rt_v5-rev1\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\VH\CLionProjects\Section2\PartA.c -o CMakeFiles\Section2.dir\PartA.c.s

CMakeFiles/Section2.dir/PartA.c.obj.requires:

.PHONY : CMakeFiles/Section2.dir/PartA.c.obj.requires

CMakeFiles/Section2.dir/PartA.c.obj.provides: CMakeFiles/Section2.dir/PartA.c.obj.requires
	$(MAKE) -f CMakeFiles\Section2.dir\build.make CMakeFiles/Section2.dir/PartA.c.obj.provides.build
.PHONY : CMakeFiles/Section2.dir/PartA.c.obj.provides

CMakeFiles/Section2.dir/PartA.c.obj.provides.build: CMakeFiles/Section2.dir/PartA.c.obj


# Object files for target Section2
Section2_OBJECTS = \
"CMakeFiles/Section2.dir/PartA.c.obj"

# External object files for target Section2
Section2_EXTERNAL_OBJECTS =

Section2.exe: CMakeFiles/Section2.dir/PartA.c.obj
Section2.exe: CMakeFiles/Section2.dir/build.make
Section2.exe: CMakeFiles/Section2.dir/linklibs.rsp
Section2.exe: CMakeFiles/Section2.dir/objects1.rsp
Section2.exe: CMakeFiles/Section2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\VH\CLionProjects\Section2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Section2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Section2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Section2.dir/build: Section2.exe

.PHONY : CMakeFiles/Section2.dir/build

CMakeFiles/Section2.dir/requires: CMakeFiles/Section2.dir/PartA.c.obj.requires

.PHONY : CMakeFiles/Section2.dir/requires

CMakeFiles/Section2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Section2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Section2.dir/clean

CMakeFiles/Section2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\VH\CLionProjects\Section2 C:\Users\VH\CLionProjects\Section2 C:\Users\VH\CLionProjects\Section2\cmake-build-debug C:\Users\VH\CLionProjects\Section2\cmake-build-debug C:\Users\VH\CLionProjects\Section2\cmake-build-debug\CMakeFiles\Section2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Section2.dir/depend

