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
CMAKE_COMMAND = /sw/bin/cmake

# The command to remove a file.
RM = /sw/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /sw/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build

# Include any dependencies generated for this target.
include json_test/CMakeFiles/json_test.dir/depend.make

# Include the progress variables for this target.
include json_test/CMakeFiles/json_test.dir/progress.make

# Include the compile flags for this target's objects.
include json_test/CMakeFiles/json_test.dir/flags.make

json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o: json_test/CMakeFiles/json_test.dir/flags.make
json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o: ../json_test/json_spirit_reader_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o -c /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_reader_test.cpp

json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.i"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_reader_test.cpp > CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.i

json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.s"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_reader_test.cpp -o CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.s

json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o.requires:
.PHONY : json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o.requires

json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o.provides: json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o.requires
	$(MAKE) -f json_test/CMakeFiles/json_test.dir/build.make json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o.provides.build
.PHONY : json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o.provides

json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o.provides.build: json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o

json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o: json_test/CMakeFiles/json_test.dir/flags.make
json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o: ../json_test/json_spirit_stream_reader_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o -c /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_stream_reader_test.cpp

json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.i"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_stream_reader_test.cpp > CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.i

json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.s"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_stream_reader_test.cpp -o CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.s

json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o.requires:
.PHONY : json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o.requires

json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o.provides: json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o.requires
	$(MAKE) -f json_test/CMakeFiles/json_test.dir/build.make json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o.provides.build
.PHONY : json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o.provides

json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o.provides.build: json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o

json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o: json_test/CMakeFiles/json_test.dir/flags.make
json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o: ../json_test/json_spirit_utils_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o -c /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_utils_test.cpp

json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.i"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_utils_test.cpp > CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.i

json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.s"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_utils_test.cpp -o CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.s

json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o.requires:
.PHONY : json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o.requires

json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o.provides: json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o.requires
	$(MAKE) -f json_test/CMakeFiles/json_test.dir/build.make json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o.provides.build
.PHONY : json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o.provides

json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o.provides.build: json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o

json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o: json_test/CMakeFiles/json_test.dir/flags.make
json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o: ../json_test/json_spirit_value_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o -c /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_value_test.cpp

json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/json_test.dir/json_spirit_value_test.cpp.i"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_value_test.cpp > CMakeFiles/json_test.dir/json_spirit_value_test.cpp.i

json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/json_test.dir/json_spirit_value_test.cpp.s"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_value_test.cpp -o CMakeFiles/json_test.dir/json_spirit_value_test.cpp.s

json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o.requires:
.PHONY : json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o.requires

json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o.provides: json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o.requires
	$(MAKE) -f json_test/CMakeFiles/json_test.dir/build.make json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o.provides.build
.PHONY : json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o.provides

json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o.provides.build: json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o

json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o: json_test/CMakeFiles/json_test.dir/flags.make
json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o: ../json_test/json_spirit_writer_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o -c /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_writer_test.cpp

json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.i"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_writer_test.cpp > CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.i

json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.s"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_spirit_writer_test.cpp -o CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.s

json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o.requires:
.PHONY : json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o.requires

json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o.provides: json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o.requires
	$(MAKE) -f json_test/CMakeFiles/json_test.dir/build.make json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o.provides.build
.PHONY : json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o.provides

json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o.provides.build: json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o

json_test/CMakeFiles/json_test.dir/utils_test.cpp.o: json_test/CMakeFiles/json_test.dir/flags.make
json_test/CMakeFiles/json_test.dir/utils_test.cpp.o: ../json_test/utils_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object json_test/CMakeFiles/json_test.dir/utils_test.cpp.o"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/json_test.dir/utils_test.cpp.o -c /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/utils_test.cpp

json_test/CMakeFiles/json_test.dir/utils_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/json_test.dir/utils_test.cpp.i"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/utils_test.cpp > CMakeFiles/json_test.dir/utils_test.cpp.i

json_test/CMakeFiles/json_test.dir/utils_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/json_test.dir/utils_test.cpp.s"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/utils_test.cpp -o CMakeFiles/json_test.dir/utils_test.cpp.s

json_test/CMakeFiles/json_test.dir/utils_test.cpp.o.requires:
.PHONY : json_test/CMakeFiles/json_test.dir/utils_test.cpp.o.requires

json_test/CMakeFiles/json_test.dir/utils_test.cpp.o.provides: json_test/CMakeFiles/json_test.dir/utils_test.cpp.o.requires
	$(MAKE) -f json_test/CMakeFiles/json_test.dir/build.make json_test/CMakeFiles/json_test.dir/utils_test.cpp.o.provides.build
.PHONY : json_test/CMakeFiles/json_test.dir/utils_test.cpp.o.provides

json_test/CMakeFiles/json_test.dir/utils_test.cpp.o.provides.build: json_test/CMakeFiles/json_test.dir/utils_test.cpp.o

json_test/CMakeFiles/json_test.dir/json_test.cpp.o: json_test/CMakeFiles/json_test.dir/flags.make
json_test/CMakeFiles/json_test.dir/json_test.cpp.o: ../json_test/json_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object json_test/CMakeFiles/json_test.dir/json_test.cpp.o"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/json_test.dir/json_test.cpp.o -c /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_test.cpp

json_test/CMakeFiles/json_test.dir/json_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/json_test.dir/json_test.cpp.i"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_test.cpp > CMakeFiles/json_test.dir/json_test.cpp.i

json_test/CMakeFiles/json_test.dir/json_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/json_test.dir/json_test.cpp.s"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test/json_test.cpp -o CMakeFiles/json_test.dir/json_test.cpp.s

json_test/CMakeFiles/json_test.dir/json_test.cpp.o.requires:
.PHONY : json_test/CMakeFiles/json_test.dir/json_test.cpp.o.requires

json_test/CMakeFiles/json_test.dir/json_test.cpp.o.provides: json_test/CMakeFiles/json_test.dir/json_test.cpp.o.requires
	$(MAKE) -f json_test/CMakeFiles/json_test.dir/build.make json_test/CMakeFiles/json_test.dir/json_test.cpp.o.provides.build
.PHONY : json_test/CMakeFiles/json_test.dir/json_test.cpp.o.provides

json_test/CMakeFiles/json_test.dir/json_test.cpp.o.provides.build: json_test/CMakeFiles/json_test.dir/json_test.cpp.o

# Object files for target json_test
json_test_OBJECTS = \
"CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o" \
"CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o" \
"CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o" \
"CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o" \
"CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o" \
"CMakeFiles/json_test.dir/utils_test.cpp.o" \
"CMakeFiles/json_test.dir/json_test.cpp.o"

# External object files for target json_test
json_test_EXTERNAL_OBJECTS =

json_test/json_test: json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o
json_test/json_test: json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o
json_test/json_test: json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o
json_test/json_test: json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o
json_test/json_test: json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o
json_test/json_test: json_test/CMakeFiles/json_test.dir/utils_test.cpp.o
json_test/json_test: json_test/CMakeFiles/json_test.dir/json_test.cpp.o
json_test/json_test: json_test/CMakeFiles/json_test.dir/build.make
json_test/json_test: json_spirit/libjson_spirit.a
json_test/json_test: json_test/CMakeFiles/json_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable json_test"
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/json_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
json_test/CMakeFiles/json_test.dir/build: json_test/json_test
.PHONY : json_test/CMakeFiles/json_test.dir/build

json_test/CMakeFiles/json_test.dir/requires: json_test/CMakeFiles/json_test.dir/json_spirit_reader_test.cpp.o.requires
json_test/CMakeFiles/json_test.dir/requires: json_test/CMakeFiles/json_test.dir/json_spirit_stream_reader_test.cpp.o.requires
json_test/CMakeFiles/json_test.dir/requires: json_test/CMakeFiles/json_test.dir/json_spirit_utils_test.cpp.o.requires
json_test/CMakeFiles/json_test.dir/requires: json_test/CMakeFiles/json_test.dir/json_spirit_value_test.cpp.o.requires
json_test/CMakeFiles/json_test.dir/requires: json_test/CMakeFiles/json_test.dir/json_spirit_writer_test.cpp.o.requires
json_test/CMakeFiles/json_test.dir/requires: json_test/CMakeFiles/json_test.dir/utils_test.cpp.o.requires
json_test/CMakeFiles/json_test.dir/requires: json_test/CMakeFiles/json_test.dir/json_test.cpp.o.requires
.PHONY : json_test/CMakeFiles/json_test.dir/requires

json_test/CMakeFiles/json_test.dir/clean:
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test && $(CMAKE_COMMAND) -P CMakeFiles/json_test.dir/cmake_clean.cmake
.PHONY : json_test/CMakeFiles/json_test.dir/clean

json_test/CMakeFiles/json_test.dir/depend:
	cd /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05 /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_test /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test/CMakeFiles/json_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : json_test/CMakeFiles/json_test.dir/depend

