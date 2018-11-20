include(${PROJECT_SOURCE_DIR}/tools-cmake/ProjectCommon.cmake)

# All the source files
set(SRC
  miscNetworking_test.cpp
  miscNetworking_test_case1.cpp
  miscNetworking_test_case2.cpp)

# We need these include directories
set(INC . ..)

# Link to the project library
set(LIB ${PROJECT_NAME})

# Finally, add the test
add_test_executable(miscNetworking_test "${SRC}" "${INC}" "${LIB}")
