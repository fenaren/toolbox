include(${PROJECT_SOURCE_DIR}/tools-cmake/ProjectCommon.cmake)

# All the source files
set(SRC TCPSocket_test.cpp)

# We need these include directories
set(INC . ..)

# Link to the project library
set(LIB ${PROJECT_NAME})

# Finally, add the test
add_test_executable(TCPSocket_test "${SRC}" "${INC}" "${LIB}")
