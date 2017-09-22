add_executable(logtest ${CMAKE_CURRENT_LIST_DIR}/logtest.cpp)
add_executable(macaddresstest ${CMAKE_CURRENT_LIST_DIR}/macaddresstest.cpp)

add_dependencies(logtest toolbox)
add_dependencies(macaddresstest toolbox)

target_include_directories(logtest PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../networking)
target_include_directories(macaddresstest PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../networking)
