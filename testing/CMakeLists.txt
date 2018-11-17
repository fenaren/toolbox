# Include common project setup
include(${PROJECT_SOURCE_DIR}/common/ProjectCommon.cmake)

# All the source files in this directory
set(SRC
  Test.cpp
  TestCases.cpp
  TestProgram.cpp)

# Add source files to the project sources; have to prepend the relative path to
# the project root for this to work
list_prepend_to_each(SRC testing/)
target_sources(${PROJECT_NAME} PRIVATE ${SRC})

# Add this directory to the project includes
target_include_directories(${PROJECT_NAME} PUBLIC .)
