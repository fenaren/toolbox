# Include common project setup
include(${PROJECT_SOURCE_DIR}/common/ProjectCommon.cmake)

set(SRC
  TCPSocket_test.cpp
  TCPSocket_test_case1.cpp
  TCPSocket_test_case2.cpp)

# We need these include directories
set(INC . ..)

# Link to the project library
set(LIB ${PROJECT_NAME})

# Finally, add the test
test_complex(TCPSocket_test "${SRC}")
