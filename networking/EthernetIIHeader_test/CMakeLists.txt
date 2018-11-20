# Include common project setup
include(${PROJECT_SOURCE_DIR}/common/ProjectCommon.cmake)

# All the source files
set(SRC EthernetIIHeader_test.cpp)

# We need these include directories
set(INC . ..)

# Link to the project library
set(LIB ${PROJECT_NAME})

# Finally, add the test
add_test_executable(EthernetIIHeader_test "${SRC}" "${INC}" "${LIB}")
