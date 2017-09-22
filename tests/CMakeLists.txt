# Add the logtest executable
add_executable(logtest ${CMAKE_CURRENT_LIST_DIR}/logtest.cpp)
add_dependencies(logtest toolbox)
target_include_directories(logtest PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../networking)
target_link_libraries(logtest toolbox)

# Add the macaddresstest executable
add_executable(macaddresstest ${CMAKE_CURRENT_LIST_DIR}/macaddresstest.cpp)
add_dependencies(macaddresstest toolbox)
target_include_directories(macaddresstest PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../networking)
target_link_libraries(macaddresstest toolbox)

add_custom_target(tests)
add_dependencies(tests logtest macaddresstest)
