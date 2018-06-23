# Add the logtest executable
add_executable(Log.ut ${CMAKE_CURRENT_LIST_DIR}/Log.ut.cpp)
add_dependencies(Log.ut toolbox)
target_include_directories(Log.ut PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../networking)
target_link_libraries(Log.ut toolbox)

# Add the macaddresstest executable
add_executable(MacAddress.ut ${CMAKE_CURRENT_LIST_DIR}/MacAddress.ut.cpp)
add_dependencies(MacAddress.ut toolbox)
target_include_directories(MacAddress.ut PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../networking)
target_link_libraries(MacAddress.ut toolbox)

# Add the program executable
add_executable(Program.ut ${CMAKE_CURRENT_LIST_DIR}/Program.ut.cpp)
add_dependencies(Program.ut toolbox)
target_include_directories(Program.ut PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../networking)
target_link_libraries(Program.ut toolbox)

# Add the PosixTimespec executable
add_executable(PosixTimespec.ut ${CMAKE_CURRENT_LIST_DIR}/PosixTimespec.ut.cpp)
add_dependencies(PosixTimespec.ut toolbox)
target_include_directories(PosixTimespec.ut PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../networking)
target_link_libraries(PosixTimespec.ut toolbox)

# Add the FixedRateProgram executable
add_executable(FixedRateProgram.ut
        ${CMAKE_CURRENT_LIST_DIR}/FixedRateProgram.ut.cpp)
add_dependencies(FixedRateProgram.ut toolbox)
target_include_directories(FixedRateProgram.ut PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../networking)
target_link_libraries(FixedRateProgram.ut toolbox)

# Add the Ipv4Address executable
add_executable(Ipv4Address.ut
        ${CMAKE_CURRENT_LIST_DIR}/Ipv4Address.ut.cpp)
add_dependencies(Ipv4Address.ut toolbox)
target_include_directories(Ipv4Address.ut PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../networking)
target_link_libraries(Ipv4Address.ut toolbox)

add_custom_target(unittests)
add_dependencies(unittests
        Log.ut
        MacAddress.ut
        Program.ut
        PosixTimespec.ut
        FixedRateProgram.ut
        Ipv4Address.ut)
