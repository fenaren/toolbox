#include <cstdint>
#include <cstring>
#include <iostream>

#include "ArpPacketEthernetIpv4_test.hpp"

#include "ArpPacketEthernetIpv4.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(ArpPacketEthernetIpv4_test);

//==============================================================================
ArpPacketEthernetIpv4_test::ArpPacketEthernetIpv4_test()
{
}

//==============================================================================
ArpPacketEthernetIpv4_test::~ArpPacketEthernetIpv4_test()
{
}

//==============================================================================
Test::Result ArpPacketEthernetIpv4_test::run()
{
    ArpPacketEthernetIpv4 apei1;
    apei1.setOper(1);
    MUST_BE_TRUE(apei1.getLengthBytes() == 28);

    unsigned char raw_apei1[28];
    apei1.writeRaw(raw_apei1);

    std::uint16_t htype;
    std::uint16_t ptype;
    std::uint8_t  hlen;
    std::uint8_t  plen;
    std::uint16_t oper;

    unsigned int offset = 0;

    offset += fieldPull(raw_apei1 + offset, htype);
    offset += fieldPull(raw_apei1 + offset, ptype);
    offset += fieldPull(raw_apei1 + offset, hlen);
    offset += fieldPull(raw_apei1 + offset, plen);
    fieldPull(raw_apei1 + offset, oper);

    MUST_BE_TRUE(htype == ArpPacketEthernetIpv4::HTYPE);
    MUST_BE_TRUE(ptype == ArpPacketEthernetIpv4::PTYPE);
    MUST_BE_TRUE(hlen  == ArpPacketEthernetIpv4::HLEN);
    MUST_BE_TRUE(plen  == ArpPacketEthernetIpv4::PLEN);
    MUST_BE_TRUE(oper  == 1);

    return Test::PASSED;
}

//==============================================================================
template <class T>
unsigned int ArpPacketEthernetIpv4_test::fieldPull(unsigned char* buffer,
                                                   T&             destination)
{
    memcpy(&destination, buffer, sizeof(T));
    return sizeof(T);
}
