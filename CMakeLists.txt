project(toolbox)
cmake_minimum_required(VERSION 3.5)

add_library(toolbox STATIC
  ${CMAKE_CURRENT_LIST_DIR}/FrameStatistics.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Log.cpp
  ${CMAKE_CURRENT_LIST_DIR}/endian.cpp)

include(${CMAKE_CURRENT_LIST_DIR}/networking/CMakeLists.txt)
