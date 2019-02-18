include(${PROJECT_SOURCE_DIR}/tools-cmake/ProjectCommon.cmake)

# All the source files
set(SRC
  RawDataField_test.cpp
  RawDataField_test_case1.cpp
  RawDataField_test_case2.cpp
  RawDataField_test_case3.cpp)

# We need these include directories
set(INC . ..)

# Libraries to link to
set(LIB ${PROJECT_NAME})

# Finally, add the test
add_test_executable(RawDataField_test "${SRC}" "${INC}" "${LIB}")
