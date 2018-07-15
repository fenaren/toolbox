add_custom_target(unittests)
add_dependencies(unittests toolbox)

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
