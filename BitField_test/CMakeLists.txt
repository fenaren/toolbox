# Include common project setup
include(${PROJECT_SOURCE_DIR}/common/ProjectCommon.cmake)

# All the source files
set(SRC
  BitField_test.cpp
  BitField_test_case1.cpp
  BitField_test_case2.cpp)

# We need these include directories
set(INC . ..)

# Libraries to link to
set(LIB ${PROJECT_NAME})

# Finally, add the test
add_test_executable(BitField_test "${SRC}" "${INC}" "${LIB}")
