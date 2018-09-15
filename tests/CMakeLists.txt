add_custom_target(${PROJECT_NAME}-tests)

# Include common project setup
include(${CMAKE_CURRENT_LIST_DIR}/../common/ProjectCommon.cmake)

set(INCLUDE_DIRS
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../networking)

set(LINK_LIBRARIES ${PROJECT_NAME})

add_test_executable(FixedRateProgramTest "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
#add_test_executable(Ipv4AddressTest      "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_test_executable(LogTest              "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
#add_test_executable(MacAddressTest       "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
#add_test_executable(OnlineStatisticsTest "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
#add_test_executable(PosixTimespecTest    "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
#add_test_executable(ProgramTest          "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
#add_test_executable(RawSocketTest        "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
#add_test_executable(TCPSocketTest        "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
#add_test_executable(UDPSocketTest        "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
#add_test_executable(miscNetworkingTest   "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
