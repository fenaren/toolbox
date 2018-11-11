#ifndef ARP_PACKET_TEST_HPP
#define ARP_PACKET_TEST_HPP

#include "Test.hpp"

#include "BitField.hpp"

class ArpPacket_test : public Test
{
public:

    // Neither of these do anything
    ArpPacket_test();
    ~ArpPacket_test();

    // Implements the test
    virtual Test::Result run();

private:

    bool isLengthBad(const BitField& bf1,
                     const BitField& bf2,
                     const BitField& bf3,
                     const BitField& bf4);

    static const unsigned int HLEN  = 6;
    static const unsigned int PLEN4 = 4;
    static const unsigned int PLEN6 = 16;
    static const unsigned int HTYPE = 1;
    static const unsigned int PTYPE = 2048;
    static const unsigned int OPER  = 42;

    BitField bfmac_good;
    BitField bfmac_bad;
    BitField bf4_good;
    BitField bf4_bad;
};

#endif
