add_custom_target(${PROJECT_NAME}-tests)

# Include common project setup
include(${CMAKE_CURRENT_LIST_DIR}/../common/ProjectCommon.cmake)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/..
    ${CMAKE_CURRENT_LIST_DIR}/../networking)

set(LINK_LIBRARIES ${PROJECT_NAME})

set(FIXED_RATE_PROGRAM_TEST_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/FixedRateProgramTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TestFRP.cpp)

add_test_executable(FixedRateProgramTest
                    "${FIXED_RATE_PROGRAM_TEST_SOURCE}"
                    "${INCLUDE_DIRS}"
                    "${LINK_LIBRARIES}")

add_test_executable_simple(
  Ipv4AddressTest "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

add_test_executable_simple(
  LogTest "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

add_test_executable_simple(
  MacAddressTest "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

#add_test_executable_simple(
#  OnlineStatisticsTest "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

#add_test_executable_simple(
#  PosixTimespecTest "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

#add_test_executable_simple(
#  ProgramTest "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

#add_test_executable_simple(
#  RawSocketTest "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

#add_test_executable_simple(
#  TCPSocketTest "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

#add_test_executable_simple(
#  UDPSocketTest "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")

#add_test_executable_simple(
#  miscNetworkingTest "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
