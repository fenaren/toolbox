project(toolbox)
cmake_minimum_required(VERSION 3.5)

# Always build with all warnings enabled
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -DRELEASE")

add_library(toolbox STATIC
  ${CMAKE_CURRENT_LIST_DIR}/Endian.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Log.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OnlineStatistics.cpp)

include(${CMAKE_CURRENT_LIST_DIR}/networking/CMakeLists.txt)
