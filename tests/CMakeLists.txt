add_custom_target(${PROJECT_NAME}-tests)

# Include common project setup
include(${CMAKE_CURRENT_LIST_DIR}/../common/ProjectCommon.cmake)

set(INCLUDE_DIRS
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../networking)

set(LINK_LIBRARIES ${PROJECT_NAME})

add_test_executable(FixedRateProgram.ut "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_test_executable(Ipv4Address.ut      "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_test_executable(LogUT               "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_test_executable(MacAddress.ut       "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_test_executable(OnlineStatistics.ut "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_test_executable(PosixTimespec.ut    "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_test_executable(Program.ut          "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_test_executable(RawSocket.ut        "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_test_executable(TCPSocket.ut        "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_test_executable(UDPSocket.ut        "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_test_executable(miscNetworking.ut   "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

# These tests can be skipped if they return 2
set_property(TEST RawSocket.ut miscNetworking.ut PROPERTY SKIP_RETURN_CODE 2)
