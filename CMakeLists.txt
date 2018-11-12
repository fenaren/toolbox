project(toolbox)

# CMake 2.6 is the oldest version of CMake that still has documentation
# available online
cmake_minimum_required(VERSION 2.6)

# Unit tests of the code in this project are located in the tests subdirectory
add_subdirectory(tests EXCLUDE_FROM_ALL)

# Include common project setup
include(${CMAKE_CURRENT_LIST_DIR}/common/ProjectCommon.cmake)

# All the source files in this directory
set(SOURCE_FILES BitField.cpp
                 DataField.cpp
                 DataPacket.cpp
                 FixedRateProgram.cpp
                 Log.cpp
                 OnlineStatistics.cpp
                 Program.cpp
                 SignalManager.cpp
                 SignalManagerImpl.cpp
                 SignalManagerFactory.cpp
                 SimpleDataField.cpp
                 Test.cpp
                 TestCases.cpp
                 TestProgram.cpp
                 misc.cpp)

# Only include POSIX code when building for platforms we know support it
if(MACOS OR LINUX)
  list(APPEND SOURCE_FILES PosixClock.cpp
                           PosixSignalManagerImpl.cpp
                           PosixTimespec.cpp)
endif(MACOS OR LINUX)

# Add the library and all the source files we're going to build (with full
# pathname prepended) in this directory
list_prepend_to_each(SOURCE_FILES ${CMAKE_CURRENT_LIST_DIR}/)
add_library(${PROJECT_NAME} ${SOURCE_FILES})

if(LINUX)
  target_link_libraries(${PROJECT_NAME} PUBLIC rt)

  # Not sure where else to put this so put it here for now;
  # scheduler-toy is for Linux only
  add_executable(scheduler-toy EXCLUDE_FROM_ALL scheduler-toy.cpp)
endif(LINUX)

# Other toolbox source files are in the networking directory, the CMakeLists.txt
# file in there will pick those up
include(${CMAKE_CURRENT_LIST_DIR}/networking/CMakeLists.txt)
