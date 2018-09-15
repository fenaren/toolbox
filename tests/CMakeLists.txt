add_custom_target(${PROJECT_NAME}-tests)

# Include common project setup
include(${CMAKE_CURRENT_LIST_DIR}/../common/ProjectCommon.cmake)

set(COMMON_INC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../networking)

set(COMMON_LIB ${PROJECT_NAME})

add_test_executable(FixedRateProgramTest "${COMMON_INC}" "${COMMON_LIB}")
#add_test_executable(Ipv4AddressTest      "${COMMON_INC}" "${COMMON_LIB}")
add_test_executable(LogTest              "${COMMON_INC}" "${COMMON_LIB}")
#add_test_executable(MacAddressTest       "${COMMON_INC}" "${COMMON_LIB}")
#add_test_executable(OnlineStatisticsTest "${COMMON_INC}" "${COMMON_LIB}")
#add_test_executable(PosixTimespecTest    "${COMMON_INC}" "${COMMON_LIB}")
#add_test_executable(ProgramTest          "${COMMON_INC}" "${COMMON_LIB}")
#add_test_executable(RawSocketTest        "${COMMON_INC}" "${COMMON_LIB}")
#add_test_executable(TCPSocketTest        "${COMMON_INC}" "${COMMON_LIB}")
#add_test_executable(UDPSocketTest        "${COMMON_INC}" "${COMMON_LIB}")
#add_test_executable(miscNetworkingTest   "${COMMON_INC}" "${COMMON_LIB}")
