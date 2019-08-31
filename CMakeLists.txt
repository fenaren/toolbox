project(tools-cpp)

# CMake 2.6 is the oldest version of CMake that still has documentation
# available online
cmake_minimum_required(VERSION 2.6)

# Use generalized settings in tools-cmake to define a bunch of baseline cmake
# stuff for this project
include(tools-cmake/ProjectCommon.cmake)

# v3.13 is when policy CMP0076 was introduced.  From cmake --help-policy:

# In CMake 3.13 and above, the ``target_sources()`` command now converts
# relative source file paths to absolute paths in the following cases:

# * Source files are added to the target's ``INTERFACE_SOURCES`` property.
# * The target's ``SOURCE_DIR`` property differs from
#   ``CMAKE_CURRENT_SOURCE_DIR``.

# We want the new behavior but we build regularly on a Linux system which is not
# at cmake v3.13 yet, so it has to use the old behavior.  The change in behavior
# requires a change in how we pass sources to target_sources

cmake_policy(VERSION ${CMAKE_VERSION})

# All the source files in this directory
set(SRC
  DataField.cpp
  DataPacket.cpp
  NoopSignalManagerImpl.cpp
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
    FixedRateProgram.cpp
    Log.cpp
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
add_subdirectory(DataField_test        EXCLUDE_FROM_ALL)
add_subdirectory(DataPacket_test       EXCLUDE_FROM_ALL)
add_subdirectory(OnlineStatistics_test EXCLUDE_FROM_ALL)
add_subdirectory(Program_test          EXCLUDE_FROM_ALL)
add_subdirectory(RawDataField_test     EXCLUDE_FROM_ALL)
add_subdirectory(SignalManager_test    EXCLUDE_FROM_ALL)
add_subdirectory(SimpleDataField_test  EXCLUDE_FROM_ALL)
add_subdirectory(TemplateClass_test    EXCLUDE_FROM_ALL)
add_subdirectory(misc_test             EXCLUDE_FROM_ALL)

if(MACOS OR LINUX)
  add_subdirectory(FixedRateProgram_test EXCLUDE_FROM_ALL)
  add_subdirectory(Log_test              EXCLUDE_FROM_ALL)
  add_subdirectory(PosixTimespec_test    EXCLUDE_FROM_ALL)
ENDIF(MACOS OR LINUX)
