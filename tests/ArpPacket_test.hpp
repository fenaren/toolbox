#ifndef ARP_PACKET_TEST_HPP
#define ARP_PACKET_TEST_HPP

#include "Test.hpp"

#include "NetworkAddress.hpp"

class ArpPacket_test : public Test
{
public:

    // Neither of these do anything
    ArpPacket_test();
    ~ArpPacket_test();

    // Implements the test
    virtual Test::Result run();

private:

    bool isLengthBad(const NetworkAddress& na1,
                     const NetworkAddress& na2,
                     const NetworkAddress& na3,
                     const NetworkAddress& na4);

    static const unsigned int HLEN  = 6;
    static const unsigned int PLEN4 = 4;
    static const unsigned int PLEN6 = 16;
    static const unsigned int HTYPE = 1;
    static const unsigned int PTYPE = 2048;
    static const unsigned int OPER  = 42;

    NetworkAddress namac_good;
    NetworkAddress namac_bad;
    NetworkAddress na4_good;
    NetworkAddress na4_bad;
};

#endif
