#include <cstdint>
#include <cstring>
#include <iostream>

#include "ArpPacketEthernetIpv4_test.hpp"

#include "ArpPacketEthernetIpv4.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

TEST_PROGRAM_MAIN(ArpPacketEthernetIpv4_test)

//==============================================================================
void ArpPacketEthernetIpv4_test::addTestCases()
{
    ADD_TEST_CASE(Length);
}

//==============================================================================
Test::Result ArpPacketEthernetIpv4_test::Length::body()
{
    // All ARP packets for Ethernet and IPv4 are 28 bytes long
    ArpPacketEthernetIpv4 apei;
    MUST_BE_TRUE(apei.getLengthBytes() == 28);

    return Test::PASSED;
}
