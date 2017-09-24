project(toolbox)
cmake_minimum_required(VERSION 3.5)

# Tests of the code in this project are located in the tests subdirectory
add_subdirectory(tests EXCLUDE_FROM_ALL)

# Flags used for all builds
set(${PROJECT_NAME}_COMMON_FLAGS "-Wall")

# Flags used for all builds on specific platforms
set(${PROJECT_NAME}_COMMON_LINUX_FLAGS "-DLINUX ${${PROJECT_NAME}_COMMON_FLAGS}")
set(${PROJECT_NAME}_COMMON_WINDOWS_FLAGS "-DWINDOWS ${${PROJECT_NAME}_COMMON_FLAGS}")

# Generate the LINUX variable
if(UNIX AND NOT APPLE)
  set(LINUX 1)
else(UNIX AND NOT APPLE)
  set(LINUX 0)
endif(UNIX AND NOT APPLE)

if(LINUX)
  set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG} ${${PROJECT_NAME}_COMMON_LINUX_FLAGS}")
  set(CMAKE_CXX_FLAGS_RELEASE
    "${CMAKE_CXX_FLAGS_RELEASE} ${${PROJECT_NAME}_COMMON_LINUX_FLAGS}")
elseif(WIN32)
  set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG} ${${PROJECT_NAME}_COMMON_WINDOWS_FLAGS}")
  set(CMAKE_CXX_FLAGS_RELEASE
    "${CMAKE_CXX_FLAGS_RELEASE} ${${PROJECT_NAME}_COMMON_WINDOWS_FLAGS}")
endif(LINUX)

# Add the library and all the source files in this directory
add_library(${PROJECT_NAME}
  ${CMAKE_CURRENT_LIST_DIR}/Endian.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Log.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OnlineStatistics.cpp)

# Other toolbox source files are in the networking directory, the CMakeLists.txt
# file in there will pick those up
include(${CMAKE_CURRENT_LIST_DIR}/networking/CMakeLists.txt)

# Not sure where else to put this so put it here for now
add_executable(scheduler-toy EXCLUDE_FROM_ALL scheduler-toy.cpp)
