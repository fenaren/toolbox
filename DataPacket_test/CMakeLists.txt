include(${PROJECT_SOURCE_DIR}/tools-cmake/ProjectCommon.cmake)

# All the source files
set(SRC
  DataPacket_test.cpp
  DataPacket_test1.cpp
  DataPacket_test2.cpp
  pullUpdatePush.cpp)

# We need these include directories
set(INC . ..)

# Link to the project library
set(LIB ${PROJECT_NAME})

# Finally, add the test
add_test_executable(DataPacket_test "${SRC}" "${INC}" "${LIB}")
