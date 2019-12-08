include(${PROJECT_SOURCE_DIR}/tools-cmake/ProjectCommon.cmake)

# All the platform-independent source files in this directory
set(SRC
  Argument.cpp
  ArgumentProcessor.cpp
  OptionalArgument.cpp)

# Add source files to the project sources.  In cmake v3.13 the behavior of
# target_sources changed and no longer requires prepending this directory to
# each source file (it does it for us).  This if can be deleted once all our
# systems are at or above cmake v3.13.
if(CMAKE_VERSION VERSION_LESS 3.13)
  list_prepend_to_each(SRC ArgumentProcessor/)
endif(CMAKE_VERSION VERSION_LESS 3.13)
target_sources(${PROJECT_NAME} PRIVATE ${SRC})

# Add this directory to the project includes
target_include_directories(${PROJECT_NAME} PUBLIC .)

# Add test subdirectories (these don't build unconditionally)
add_subdirectory(ArgumentProcessor_test EXCLUDE_FROM_ALL)
