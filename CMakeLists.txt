project(toolbox)

# CMake 2.6 is the oldest version of CMake that still has documentation
# available online
cmake_minimum_required(VERSION 2.6)

# Unit tests of the code in this project are located in the tests subdirectory
add_subdirectory(tests EXCLUDE_FROM_ALL)

# Include common project setup
include(${CMAKE_CURRENT_LIST_DIR}/common/ProjectCommon.cmake)

# Add the library and all the source files in this directory
add_library(${PROJECT_NAME}
  ${CMAKE_CURRENT_LIST_DIR}/BitField.cpp
  ${CMAKE_CURRENT_LIST_DIR}/DataField.cpp
  ${CMAKE_CURRENT_LIST_DIR}/DataPacket.cpp
  ${CMAKE_CURRENT_LIST_DIR}/FixedRateProgram.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Log.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OnlineStatistics.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Program.cpp
  ${CMAKE_CURRENT_LIST_DIR}/SignalManager.cpp
  ${CMAKE_CURRENT_LIST_DIR}/SignalManagerImpl.cpp
  ${CMAKE_CURRENT_LIST_DIR}/SignalManagerFactory.cpp
  ${CMAKE_CURRENT_LIST_DIR}/SimpleDataField.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Test.cpp
  ${CMAKE_CURRENT_LIST_DIR}/TestCases.cpp
  ${CMAKE_CURRENT_LIST_DIR}/TestProgram.cpp
  ${CMAKE_CURRENT_LIST_DIR}/misc.cpp)

# Only include POSIX code when building for platforms we know support it
if(MACOS OR LINUX)
  target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/PosixClock.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PosixSignalManagerImpl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PosixTimespec.cpp)
endif(MACOS OR LINUX)

if(LINUX)
  target_link_libraries(${PROJECT_NAME} PUBLIC rt)

  # Not sure where else to put this so put it here for now;
  # scheduler-toy is for Linux only
  add_executable(scheduler-toy EXCLUDE_FROM_ALL scheduler-toy.cpp)
endif(LINUX)

# Other toolbox source files are in the networking directory, the CMakeLists.txt
# file in there will pick those up
include(${CMAKE_CURRENT_LIST_DIR}/networking/CMakeLists.txt)
