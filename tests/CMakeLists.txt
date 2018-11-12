add_custom_target(${PROJECT_NAME}-tests)

# Include common project setup
include(${CMAKE_CURRENT_LIST_DIR}/../common/ProjectCommon.cmake)

# All the tests use this set of include directories
set(INC . .. ../networking)
list_prepend_to_each(INC ${CMAKE_CURRENT_LIST_DIR}/)

# All the tests link against the project library and that's it
set(LIB ${PROJECT_NAME})

# ArpPacket_test
add_test_executable_simple(ArpPacket_test "${INC}" "${LIB}")

# ArpPacketEthernetIpv4_test
add_test_executable_simple(ArpPacketEthernetIpv4_test "${INC}" "${LIB}")

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

# EthernetIIHeader_test
add_test_executable_simple(EthernetIIHeader_test "${INC}" "${LIB}")

# FixedRateProgram_test
set(SRC FixedRateProgram_test.cpp
        FixedRateProgram_test_tc1.cpp)
list_prepend_to_each(SRC ${CMAKE_CURRENT_LIST_DIR}/)
add_test_executable(FixedRateProgram_test "${SRC}" "${INC}" "${LIB}")

# Ipv4Address_test
add_test_executable_simple(Ipv4Address_test "${INC}" "${LIB}")

# Log_test
add_test_executable_simple(Log_test "${INC}" "${LIB}")

# MacAddress_test
add_test_executable_simple(MacAddress_test "${INC}" "${LIB}")

# OnlineStatistics_test
add_test_executable_simple(OnlineStatistics_test "${INC}" "${LIB}")

# PosixTimespec_test
add_test_executable_simple(PosixTimespec_test "${INC}" "${LIB}")

# Program_test
set(SRC Program_test.cpp
        Program_test_tc1.cpp)
list_prepend_to_each(SRC ${CMAKE_CURRENT_LIST_DIR}/)
add_test_executable(Program_test "${SRC}" "${INC}" "${LIB}")

# RawSocket_test
add_test_executable_simple(RawSocket_test "${INC}" "${LIB}")

# SimpleDataField_test
add_test_executable_simple(SimpleDataField_test "${INC}" "${LIB}")

# SignalManager_test
add_test_executable_simple(SignalManager_test "${INC}" "${LIB}")

# TCPSocket_test
set(SRC TCPSocket_test.cpp
        TCPSocket_test_case1.cpp
        TCPSocket_test_case2.cpp)
list_prepend_to_each(SRC ${CMAKE_CURRENT_LIST_DIR}/)
add_test_executable(TCPSocket_test "${SRC}" "${INC}" "${LIB}")

# UDPSocket_test
add_test_executable_simple(UDPSocket_test "${INC}" "${LIB}")

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
