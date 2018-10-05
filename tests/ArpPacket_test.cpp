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
    ArpPacket arp_packet(6, 4);
    MUST_BE_TRUE(arp_packet.getLengthBytes() == 28);

    return Test::PASSED;
}
