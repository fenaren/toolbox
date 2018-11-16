# Include common project setup
include(${PROJECT_SOURCE_DIR}/common/ProjectCommon.cmake)

set(SRC
  Program_test.cpp
  Program_test_tc1.cpp)

# We need these include directories
set(INC . ..)

# Link to the project library
set(LIB ${PROJECT_NAME})

# Finally, add the test
test_complex(Program_test "${SRC}")
