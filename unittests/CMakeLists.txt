add_custom_target(unittests)
add_dependencies(unittests toolbox)

# Include common project setup
include(${CMAKE_CURRENT_LIST_DIR}/../common/ProjectCommon.cmake)

function(add_unittest UT_NAME)
  add_executable(${UT_NAME} ${CMAKE_CURRENT_LIST_DIR}/${UT_NAME}.cpp)
  add_dependencies(unittests ${UT_NAME})
  target_include_directories(${UT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/..
    ${CMAKE_CURRENT_LIST_DIR}/../networking)
  target_link_libraries(${UT_NAME} toolbox)
endfunction(add_unittest)

add_unittest(FixedRateProgram.ut)
add_unittest(Ipv4Address.ut)
add_unittest(Log.ut)
add_unittest(MacAddress.ut)
add_unittest(Program.ut)
add_unittest(OnlineStatistics.ut)
add_unittest(PosixTimespec.ut)
add_unittest(RawSocket.ut)
add_unittest(TCPSocket.ut)
add_unittest(UDPSocket.ut)

# This test is only useful on Linux right now
if(LINUX)
  add_unittest(miscNetworking.ut)
endif(LINUX)
