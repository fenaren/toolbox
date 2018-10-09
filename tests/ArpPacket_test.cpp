#include <iostream>

#include "ArpPacket_test.hpp"

#include "ArpPacket.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(ArpPacket_test);

//==============================================================================
ArpPacket_test::ArpPacket_test()
{
}

//==============================================================================
ArpPacket_test::~ArpPacket_test()
{
}

//==============================================================================
Test::Result ArpPacket_test::run()
{
    // Ethernet and IPv4
    ArpPacket arp_packet1(6, 4);
    MUST_BE_TRUE(arp_packet1.getLengthBytes() == 28);

    // Ethernet and IPv6
    ArpPacket arp_packet2(6, 16);
    MUST_BE_TRUE(arp_packet2.getLengthBytes() == 52);

    return Test::PASSED;
}
