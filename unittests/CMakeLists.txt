add_custom_target(unittests-${PROJECT_NAME})
#add_dependencies(unittests-${PROJECT_NAME} toolbox)

# Include common project setup
include(${CMAKE_CURRENT_LIST_DIR}/../common/ProjectCommon.cmake)

set(INCLUDE_DIRS
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../networking)

set(LINK_LIBRARIES toolbox)

add_unittest(FixedRateProgram.ut "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_unittest(Ipv4Address.ut      "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_unittest(Log.ut              "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_unittest(MacAddress.ut       "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_unittest(Program.ut          "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_unittest(OnlineStatistics.ut "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_unittest(PosixTimespec.ut    "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_unittest(RawSocket.ut        "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_unittest(TCPSocket.ut        "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_unittest(UDPSocket.ut        "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
add_unittest(miscNetworking.ut   "${INCLUDE_DIRS}" "${LINK_LIBRARIES}")
