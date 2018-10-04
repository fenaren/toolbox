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
    std::cout << arp_packet.getLengthBytes() << "\n";

    return Test::PASSED;
}
