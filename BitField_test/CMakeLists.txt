# Include common project setup
include(${PROJECT_SOURCE_DIR}/common/ProjectCommon.cmake)

# All the platform-independent source files in this directory
set(SRC
  BitField_test.cpp
  BitField_test_case1.cpp
  BitField_test_case2.cpp)

# We need these include directories
set(INC . ..)

# Link to the project library
set(LIB ${PROJECT_NAME})

# Finally, add the test
test_complex(BitField_test "${SRC}")
