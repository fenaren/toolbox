add_custom_target(${PROJECT_NAME}-tests)

# Include common project setup
include(${CMAKE_CURRENT_LIST_DIR}/../common/ProjectCommon.cmake)

# All the tests use this set of include directories
set(INC . .. ../networking)
list_prepend_to_each(INC ${CMAKE_CURRENT_LIST_DIR}/)

# All the tests link against the project library and that's it
set(LIB ${PROJECT_NAME})

# Add all the "simple" tests that consist of only a single source file
test_simple(ArpPacket_test)
test_simple(ArpPacketEthernetIpv4_test)
test_simple(EthernetIIHeader_test)
test_simple(Ipv4Address_test)
test_simple(Log_test)
test_simple(MacAddress_test)
test_simple(OnlineStatistics_test)
test_simple(PosixTimespec_test)
test_simple(RawSocket_test)
test_simple(SimpleDataField_test)
test_simple(SignalManager_test)

# UDPSocket_test
add_test_executable_simple(UDPSocket_test "${INC}" "${LIB}")

# BitField_test
set(SRC BitField_test.cpp
        BitField_test_case1.cpp
        BitField_test_case2.cpp)
list_prepend_to_each(SRC ${CMAKE_CURRENT_LIST_DIR}/)
add_test_executable(BitField_test "${SRC}" "${INC}" "${LIB}")

# DataPacket_test
set(SRC DataPacket_test.cpp
        DataPacket_test_case1.cpp
        DataPacket_test_case2.cpp
        DataPacket_test_case3.cpp
        DataPacket_test1.cpp
        DataPacket_test2.cpp)
list_prepend_to_each(SRC ${CMAKE_CURRENT_LIST_DIR}/)
add_test_executable(DataPacket_test "${SRC}" "${INC}" "${LIB}")

# FixedRateProgram_test
set(SRC FixedRateProgram_test.cpp
        FixedRateProgram_test_tc1.cpp)
list_prepend_to_each(SRC ${CMAKE_CURRENT_LIST_DIR}/)
add_test_executable(FixedRateProgram_test "${SRC}" "${INC}" "${LIB}")

# Program_test
set(SRC Program_test.cpp
        Program_test_tc1.cpp)
list_prepend_to_each(SRC ${CMAKE_CURRENT_LIST_DIR}/)
add_test_executable(Program_test "${SRC}" "${INC}" "${LIB}")

# TCPSocket_test
set(SRC TCPSocket_test.cpp
        TCPSocket_test_case1.cpp
        TCPSocket_test_case2.cpp)
list_prepend_to_each(SRC ${CMAKE_CURRENT_LIST_DIR}/)
add_test_executable(TCPSocket_test "${SRC}" "${INC}" "${LIB}")

# misc
set(SRC misc_test.cpp
        misc_test_case1.cpp)
list_prepend_to_each(SRC ${CMAKE_CURRENT_LIST_DIR}/)
add_test_executable(misc_test "${SRC}" "${INC}" "${LIB}")

# miscNetworking_test
set(SRC miscNetworking_test.cpp
        miscNetworking_test_case1.cpp
        miscNetworking_test_case2.cpp)
list_prepend_to_each(SRC ${CMAKE_CURRENT_LIST_DIR}/)
add_test_executable(miscNetworking_test "${SRC}" "${INC}" "${LIB}")
