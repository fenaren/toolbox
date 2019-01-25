include(${PROJECT_SOURCE_DIR}/tools-cmake/ProjectCommon.cmake)

# All the source files
set(SRC
  SimpleDataField_test.cpp
  SimpleDataField_test_case1.cpp
  SimpleDataField_test_case2.cpp)

# We need these include directories
set(INC . ..)

# Link to the project library
set(LIB ${PROJECT_NAME})

# Finally, add the test
add_test_executable(SimpleDataField_test "${SRC}" "${INC}" "${LIB}")
