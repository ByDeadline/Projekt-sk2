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
CMAKE_SOURCE_DIR = /home/kuba/Documents/sk2/backend

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kuba/Documents/sk2/backend/build

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/main.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/main.cpp.o: ../main.cpp
CMakeFiles/server.dir/main.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuba/Documents/sk2/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/main.cpp.o -MF CMakeFiles/server.dir/main.cpp.o.d -o CMakeFiles/server.dir/main.cpp.o -c /home/kuba/Documents/sk2/backend/main.cpp

CMakeFiles/server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kuba/Documents/sk2/backend/main.cpp > CMakeFiles/server.dir/main.cpp.i

CMakeFiles/server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kuba/Documents/sk2/backend/main.cpp -o CMakeFiles/server.dir/main.cpp.s

CMakeFiles/server.dir/libraries/cpp/Config.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/libraries/cpp/Config.cpp.o: ../libraries/cpp/Config.cpp
CMakeFiles/server.dir/libraries/cpp/Config.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuba/Documents/sk2/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/libraries/cpp/Config.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/libraries/cpp/Config.cpp.o -MF CMakeFiles/server.dir/libraries/cpp/Config.cpp.o.d -o CMakeFiles/server.dir/libraries/cpp/Config.cpp.o -c /home/kuba/Documents/sk2/backend/libraries/cpp/Config.cpp

CMakeFiles/server.dir/libraries/cpp/Config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/libraries/cpp/Config.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kuba/Documents/sk2/backend/libraries/cpp/Config.cpp > CMakeFiles/server.dir/libraries/cpp/Config.cpp.i

CMakeFiles/server.dir/libraries/cpp/Config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/libraries/cpp/Config.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kuba/Documents/sk2/backend/libraries/cpp/Config.cpp -o CMakeFiles/server.dir/libraries/cpp/Config.cpp.s

CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.o: ../libraries/cpp/GlobalSettings.cpp
CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuba/Documents/sk2/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.o -MF CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.o.d -o CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.o -c /home/kuba/Documents/sk2/backend/libraries/cpp/GlobalSettings.cpp

CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kuba/Documents/sk2/backend/libraries/cpp/GlobalSettings.cpp > CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.i

CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kuba/Documents/sk2/backend/libraries/cpp/GlobalSettings.cpp -o CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.s

CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.o: ../libraries/cpp/IRequestData.cpp
CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuba/Documents/sk2/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.o -MF CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.o.d -o CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.o -c /home/kuba/Documents/sk2/backend/libraries/cpp/IRequestData.cpp

CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kuba/Documents/sk2/backend/libraries/cpp/IRequestData.cpp > CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.i

CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kuba/Documents/sk2/backend/libraries/cpp/IRequestData.cpp -o CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.s

CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.o: ../libraries/cpp/Lobby.cpp
CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuba/Documents/sk2/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.o -MF CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.o.d -o CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.o -c /home/kuba/Documents/sk2/backend/libraries/cpp/Lobby.cpp

CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kuba/Documents/sk2/backend/libraries/cpp/Lobby.cpp > CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.i

CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kuba/Documents/sk2/backend/libraries/cpp/Lobby.cpp -o CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.s

CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.o: ../libraries/cpp/LobbyHandler.cpp
CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuba/Documents/sk2/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.o -MF CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.o.d -o CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.o -c /home/kuba/Documents/sk2/backend/libraries/cpp/LobbyHandler.cpp

CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kuba/Documents/sk2/backend/libraries/cpp/LobbyHandler.cpp > CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.i

CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kuba/Documents/sk2/backend/libraries/cpp/LobbyHandler.cpp -o CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.s

CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.o: ../libraries/cpp/LobbyRequestConverter.cpp
CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuba/Documents/sk2/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.o -MF CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.o.d -o CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.o -c /home/kuba/Documents/sk2/backend/libraries/cpp/LobbyRequestConverter.cpp

CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kuba/Documents/sk2/backend/libraries/cpp/LobbyRequestConverter.cpp > CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.i

CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kuba/Documents/sk2/backend/libraries/cpp/LobbyRequestConverter.cpp -o CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.s

CMakeFiles/server.dir/libraries/cpp/Log.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/libraries/cpp/Log.cpp.o: ../libraries/cpp/Log.cpp
CMakeFiles/server.dir/libraries/cpp/Log.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuba/Documents/sk2/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/server.dir/libraries/cpp/Log.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/libraries/cpp/Log.cpp.o -MF CMakeFiles/server.dir/libraries/cpp/Log.cpp.o.d -o CMakeFiles/server.dir/libraries/cpp/Log.cpp.o -c /home/kuba/Documents/sk2/backend/libraries/cpp/Log.cpp

CMakeFiles/server.dir/libraries/cpp/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/libraries/cpp/Log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kuba/Documents/sk2/backend/libraries/cpp/Log.cpp > CMakeFiles/server.dir/libraries/cpp/Log.cpp.i

CMakeFiles/server.dir/libraries/cpp/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/libraries/cpp/Log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kuba/Documents/sk2/backend/libraries/cpp/Log.cpp -o CMakeFiles/server.dir/libraries/cpp/Log.cpp.s

CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.o: ../libraries/cpp/RequestConverter.cpp
CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuba/Documents/sk2/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.o -MF CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.o.d -o CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.o -c /home/kuba/Documents/sk2/backend/libraries/cpp/RequestConverter.cpp

CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kuba/Documents/sk2/backend/libraries/cpp/RequestConverter.cpp > CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.i

CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kuba/Documents/sk2/backend/libraries/cpp/RequestConverter.cpp -o CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.s

CMakeFiles/server.dir/libraries/cpp/Server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/libraries/cpp/Server.cpp.o: ../libraries/cpp/Server.cpp
CMakeFiles/server.dir/libraries/cpp/Server.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuba/Documents/sk2/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/server.dir/libraries/cpp/Server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/libraries/cpp/Server.cpp.o -MF CMakeFiles/server.dir/libraries/cpp/Server.cpp.o.d -o CMakeFiles/server.dir/libraries/cpp/Server.cpp.o -c /home/kuba/Documents/sk2/backend/libraries/cpp/Server.cpp

CMakeFiles/server.dir/libraries/cpp/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/libraries/cpp/Server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kuba/Documents/sk2/backend/libraries/cpp/Server.cpp > CMakeFiles/server.dir/libraries/cpp/Server.cpp.i

CMakeFiles/server.dir/libraries/cpp/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/libraries/cpp/Server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kuba/Documents/sk2/backend/libraries/cpp/Server.cpp -o CMakeFiles/server.dir/libraries/cpp/Server.cpp.s

CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.o: ../libraries/cpp/TCPHandler.cpp
CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuba/Documents/sk2/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.o -MF CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.o.d -o CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.o -c /home/kuba/Documents/sk2/backend/libraries/cpp/TCPHandler.cpp

CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kuba/Documents/sk2/backend/libraries/cpp/TCPHandler.cpp > CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.i

CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kuba/Documents/sk2/backend/libraries/cpp/TCPHandler.cpp -o CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.s

CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.o: ../libraries/cpp/UserHandler.cpp
CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuba/Documents/sk2/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.o -MF CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.o.d -o CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.o -c /home/kuba/Documents/sk2/backend/libraries/cpp/UserHandler.cpp

CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kuba/Documents/sk2/backend/libraries/cpp/UserHandler.cpp > CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.i

CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kuba/Documents/sk2/backend/libraries/cpp/UserHandler.cpp -o CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.s

CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.o: ../libraries/cpp/UserRequestConverter.cpp
CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuba/Documents/sk2/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.o -MF CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.o.d -o CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.o -c /home/kuba/Documents/sk2/backend/libraries/cpp/UserRequestConverter.cpp

CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kuba/Documents/sk2/backend/libraries/cpp/UserRequestConverter.cpp > CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.i

CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kuba/Documents/sk2/backend/libraries/cpp/UserRequestConverter.cpp -o CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/main.cpp.o" \
"CMakeFiles/server.dir/libraries/cpp/Config.cpp.o" \
"CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.o" \
"CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.o" \
"CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.o" \
"CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.o" \
"CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.o" \
"CMakeFiles/server.dir/libraries/cpp/Log.cpp.o" \
"CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.o" \
"CMakeFiles/server.dir/libraries/cpp/Server.cpp.o" \
"CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.o" \
"CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.o" \
"CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/main.cpp.o
server: CMakeFiles/server.dir/libraries/cpp/Config.cpp.o
server: CMakeFiles/server.dir/libraries/cpp/GlobalSettings.cpp.o
server: CMakeFiles/server.dir/libraries/cpp/IRequestData.cpp.o
server: CMakeFiles/server.dir/libraries/cpp/Lobby.cpp.o
server: CMakeFiles/server.dir/libraries/cpp/LobbyHandler.cpp.o
server: CMakeFiles/server.dir/libraries/cpp/LobbyRequestConverter.cpp.o
server: CMakeFiles/server.dir/libraries/cpp/Log.cpp.o
server: CMakeFiles/server.dir/libraries/cpp/RequestConverter.cpp.o
server: CMakeFiles/server.dir/libraries/cpp/Server.cpp.o
server: CMakeFiles/server.dir/libraries/cpp/TCPHandler.cpp.o
server: CMakeFiles/server.dir/libraries/cpp/UserHandler.cpp.o
server: CMakeFiles/server.dir/libraries/cpp/UserRequestConverter.cpp.o
server: CMakeFiles/server.dir/build.make
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kuba/Documents/sk2/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server
.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /home/kuba/Documents/sk2/backend/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kuba/Documents/sk2/backend /home/kuba/Documents/sk2/backend /home/kuba/Documents/sk2/backend/build /home/kuba/Documents/sk2/backend/build /home/kuba/Documents/sk2/backend/build/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

