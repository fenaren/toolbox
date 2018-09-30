add_custom_target(${PROJECT_NAME}-tests)

# Include common project setup
include(${CMAKE_CURRENT_LIST_DIR}/../common/ProjectCommon.cmake)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/..
    ${CMAKE_CURRENT_LIST_DIR}/../networking)

set(LINK_LIBRARIES ${PROJECT_NAME})


# FixedRateProgram_test
set(FIXED_RATE_PROGRAM_TEST_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/FixedRateProgram_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FixedRateProgram_test_tc1.cpp)
add_test_executable(FixedRateProgram_test
                    "${FIXED_RATE_PROGRAM_TEST_SOURCE}"
                    "${INCLUDE_DIRS}"
                    "${LINK_LIBRARIES}")

# Ipv4Address_test
add_test_executable_simple(
  Ipv4Address_test "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

# Log_test
add_test_executable_simple(
  Log_test "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

# MacAddress_test
add_test_executable_simple(
  MacAddress_test "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

# NetworkAddress_test
add_test_executable_simple(
  NetworkAddress_test "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

# OnlineStatistics_test
add_test_executable_simple(
  OnlineStatistics_test "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

# PosixTimespec_test
add_test_executable_simple(
  PosixTimespec_test "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

# Program_test
set(PROGRAM_TEST_SOURCE Program_test.cpp Program_test_tc1.cpp)
add_test_executable(Program_test
                    "${PROGRAM_TEST_SOURCE}"
                    "${INCLUDE_DIRS}"
                    "${LINK_LIBRARIES}")

# RawSocket_test
add_test_executable_simple(
  RawSocket_test "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

# TCPSocket_test
set(TCP_SOCKET_TEST_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/TCPSocket_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TCPSocket_test_case1.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TCPSocket_test_case2.cpp)
add_test_executable(TCPSocket_test
                    "${TCP_SOCKET_TEST_SOURCE}"
                    "${INCLUDE_DIRS}"
                    "${LINK_LIBRARIES}")

# UDPSocket_test
add_test_executable_simple(
  UDPSocket_test "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

# miscNetworking_test
set(MISC_NETWORKING_TEST_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/miscNetworking_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/miscNetworking_test_case1.cpp
    ${CMAKE_CURRENT_LIST_DIR}/miscNetworking_test_case2.cpp)
add_test_executable(miscNetworking_test
                    "${MISC_NETWORKING_TEST_SOURCE}"
                    "${INCLUDE_DIRS}"
                    "${LINK_LIBRARIES}")
