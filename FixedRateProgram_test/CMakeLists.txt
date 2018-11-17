# Include common project setup
include(${PROJECT_SOURCE_DIR}/common/ProjectCommon.cmake)

# All the source files
set(SRC
  FixedRateProgram_test.cpp
  FixedRateProgram_test_tc1.cpp)

# We need these include directories
set(INC . ..)

# Link to the project library
set(LIB ${PROJECT_NAME})

# Finally, add the test
add_test_executable(FixedRateProgram_test "${SRC}" "${INC}" "${LIB}")
