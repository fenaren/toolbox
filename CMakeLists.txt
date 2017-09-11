project(toolbox)
cmake_minimum_required(VERSION 3.5)

set(SRC
  FrameStatistics.cpp
  Log.cpp
  endian.cpp)

add_library(toolbox ${SRC})

include(networking/CMakeLists.txt)
