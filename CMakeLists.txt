project(toolbox)
cmake_minimum_required(VERSION 3.5)

set(COMMON_FLAGS "-Wall")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${COMMON_FLAGS} -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${COMMON_FLAGS} -DRELEASE")

add_library(toolbox STATIC
  ${CMAKE_CURRENT_LIST_DIR}/Endian.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Log.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OnlineStatistics.cpp)

include(${CMAKE_CURRENT_LIST_DIR}/networking/CMakeLists.txt)
