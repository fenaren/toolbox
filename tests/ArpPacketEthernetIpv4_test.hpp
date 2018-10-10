#ifndef ARP_PACKET_ETHERNET_IPV4_TEST_HPP
#define ARP_PACKET_ETHERNET_IPV4_TEST_HPP

#include "Test.hpp"

class ArpPacketEthernetIpv4_test : public Test
{
public:

    // Neither of these do anything
    ArpPacketEthernetIpv4_test();
    ~ArpPacketEthernetIpv4_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
