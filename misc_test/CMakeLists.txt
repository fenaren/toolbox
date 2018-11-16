# Include common project setup
include(${PROJECT_SOURCE_DIR}/common/ProjectCommon.cmake)

set(SRC
  misc_test.cpp
  misc_test_case1.cpp)

# We need these include directories
set(INC . ..)

# Link to the project library
set(LIB ${PROJECT_NAME})

# Finally, add the test
test_complex(misc_test "${SRC}")
