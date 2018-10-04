#ifndef ARP_PACKET_TEST_HPP
#define ARP_PACKET_TEST_HPP

#include "Test.hpp"

class ArpPacket_test : public Test
{
public:

    // Neither of these do anything
    ArpPacket_test();
    ~ArpPacket_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
