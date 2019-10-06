include(${PROJECT_SOURCE_DIR}/tools-cmake/ProjectCommon.cmake)

# All the source files
set(SRC
  HelloWorld.cpp
  PosixFixedRateProgramImpl_test.cpp)

# We need these include directories
set(INC . ..)

# Link to the project library
set(LIB ${PROJECT_NAME})

# Finally, add the test
add_test_executable(PosixFixedRateProgramImpl_test "${SRC}" "${INC}" "${LIB}")
