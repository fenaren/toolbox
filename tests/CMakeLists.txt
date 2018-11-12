add_custom_target(${PROJECT_NAME}-tests)

# Include common project setup
include(${CMAKE_CURRENT_LIST_DIR}/../common/ProjectCommon.cmake)

# All the tests use this set of include directories
set(INC . .. ../networking)
list_prepend_to_each(INC ${CMAKE_CURRENT_LIST_DIR}/)

# All the tests link against the project library and that's it
set(LIB ${PROJECT_NAME})

# Add all the "simple" tests that consist of only a single source file.  The
# test_simple macro passes the INC and LIB lists in for us
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
test_simple(UDPSocket_test)

# Below here are all the more complicated tests with more than one source file.
# Source file lists are all defined first, then their corresponding tests.

set(SRC_BIT_FIELD_TEST
    BitField_test.cpp
    BitField_test_case1.cpp
    BitField_test_case2.cpp)

set(SRC_DATA_PACKET_TEST
    DataPacket_test.cpp
    DataPacket_test_case1.cpp
    DataPacket_test_case2.cpp
    DataPacket_test_case3.cpp
    DataPacket_test1.cpp
    DataPacket_test2.cpp)

set(SRC_FIXED_RATE_PROGRAM_TEST
    FixedRateProgram_test.cpp
    FixedRateProgram_test_tc1.cpp)

set(SRC_PROGRAM_TEST
    Program_test.cpp
    Program_test_tc1.cpp)

set(SRC_TCP_SOCKET_TEST
    TCPSocket_test.cpp
    TCPSocket_test_case1.cpp
    TCPSocket_test_case2.cpp)

set(SRC_MISC_TEST
    misc_test.cpp
    misc_test_case1.cpp)

set(SRC_MISC_NETWORKING_TEST
    miscNetworking_test.cpp
    miscNetworking_test_case1.cpp
    miscNetworking_test_case2.cpp)

test_complex(BitField_test         "${SRC_BIT_FIELD_TEST}")
test_complex(DataPacket_test       "${SRC_DATA_PACKET_TEST}")
test_complex(FixedRateProgram_test "${SRC_FIXED_RATE_PROGRAM_TEST}")
test_complex(Program_test          "${SRC_PROGRAM_TEST}")
test_complex(TCPSocket_test        "${SRC_TCP_SOCKET_TEST}")
test_complex(misc_test             "${SRC_MISC_TEST}")
test_complex(miscNetworking_test   "${SRC_MISC_NETWORKING_TEST}")
