project(tools-cpp)

# CMake 2.6 is the oldest version of CMake that still has documentation
# available online
cmake_minimum_required(VERSION 2.6)

# Use cmake tools to help with this project
include(tools-cmake/ProjectCommon.cmake)

# All the source files in this directory
set(SRC
  DataField.cpp
  DataPacket.cpp
  FixedRateProgram.cpp
  Log.cpp
  OnlineStatistics.cpp
  Program.cpp
  RawDataField.cpp
  SignalManager.cpp
  SignalManagerImpl.cpp
  SignalManagerFactory.cpp
  SimpleDataField.cpp
  TemplateClass.cpp
  misc.cpp)

# Only include POSIX code when building for platforms we know support it
if(MACOS OR LINUX)
  list(APPEND SRC
    PosixClock.cpp
    PosixSignalManagerImpl.cpp
    PosixTimespec.cpp)
endif(MACOS OR LINUX)

# Add source files to the project sources
add_library(${PROJECT_NAME} ${SRC})

# Add this directory to the project includes
target_include_directories(${PROJECT_NAME} PUBLIC .)

if(LINUX)
  target_link_libraries(${PROJECT_NAME} PUBLIC rt)

  # Not sure where else to put this so put it here for now; scheduler-toy is for
  # Linux only
  add_executable(scheduler-toy EXCLUDE_FROM_ALL scheduler-toy.cpp)
endif(LINUX)

# Add standard subdirectories (these build unconditionally)
add_subdirectory(networking)
add_subdirectory(testing)

# Add test subdirectories (these don't build unconditionally)
#add_subdirectory(BitField_test         EXCLUDE_FROM_ALL)
add_subdirectory(DataPacket_test       EXCLUDE_FROM_ALL)
add_subdirectory(FixedRateProgram_test EXCLUDE_FROM_ALL)
add_subdirectory(Log_test              EXCLUDE_FROM_ALL)
add_subdirectory(OnlineStatistics_test EXCLUDE_FROM_ALL)
add_subdirectory(PosixTimespec_test    EXCLUDE_FROM_ALL)
add_subdirectory(Program_test          EXCLUDE_FROM_ALL)
add_subdirectory(RawDataField_test     EXCLUDE_FROM_ALL)
add_subdirectory(SignalManager_test    EXCLUDE_FROM_ALL)
add_subdirectory(SimpleDataField_test  EXCLUDE_FROM_ALL)
add_subdirectory(TemplateClass_test    EXCLUDE_FROM_ALL)
add_subdirectory(misc_test             EXCLUDE_FROM_ALL)
