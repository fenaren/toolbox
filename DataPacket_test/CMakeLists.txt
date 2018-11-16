# Include common project setup
include(${PROJECT_SOURCE_DIR}/common/ProjectCommon.cmake)

# All the platform-independent source files in this directory
set(SRC
  DataPacket_test.cpp
  DataPacket_test1.cpp
  DataPacket_test2.cpp
  DataPacket_test_case1.cpp
  DataPacket_test_case2.cpp
  DataPacket_test_case3.cpp)

# We need these include directories
set(INC . ..)

# Link to the project library
set(LIB ${PROJECT_NAME})

# Finally, add the test
test_complex(DataPacket_test "${SRC}")
