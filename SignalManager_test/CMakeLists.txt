include(${PROJECT_SOURCE_DIR}/tools-cmake/ProjectCommon.cmake)

# All the source files
set(SRC SignalManager_test.cpp)

# We need these include directories
set(INC . ..)

# Link to the project library
set(LIB ${PROJECT_NAME})

# Finally, add the test, but not if we're on Windows (there isn't a meaningful
# SignalManager implementation for Windows yet)
if(NOT WIN32)
  add_test_executable(SignalManager_test "${SRC}" "${INC}" "${LIB}")
endif(NOT WIN32)
