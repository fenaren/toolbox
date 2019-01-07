#include <cstdint>
#include <cstring>
#include <iostream>

#include "ArpPacketEthernetIpv4.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TRIVIAL_TEST(ArpPacketEthernetIpv4_test);

template <class T>
unsigned int fieldPull(unsigned char* buffer, T& destination);

//==============================================================================
Test::Result ArpPacketEthernetIpv4_test::body()
{
    // ARP packets carrying IPv4 and Ethernet addresses are exactly this length
    const unsigned int PACKET_LENGTH = 28;

    const unsigned int MAC_LENGTH_BYTES  = 6;
    const unsigned int IPV4_LENGTH_BYTES = 4;

    unsigned char ipv41[IPV4_LENGTH_BYTES];
    unsigned char ipv42[IPV4_LENGTH_BYTES];
    unsigned char mac1[MAC_LENGTH_BYTES];
    unsigned char mac2[MAC_LENGTH_BYTES];

    unsigned char ipv41copy[IPV4_LENGTH_BYTES];
    unsigned char ipv42copy[IPV4_LENGTH_BYTES];
    unsigned char mac1copy[MAC_LENGTH_BYTES];
    unsigned char mac2copy[MAC_LENGTH_BYTES];

    memset(&ipv41, 1, IPV4_LENGTH_BYTES);
    memset(&ipv42, 2, IPV4_LENGTH_BYTES);
    memset(&mac1,  1, MAC_LENGTH_BYTES);
    memset(&mac2,  2, MAC_LENGTH_BYTES);

    memcpy(ipv41copy, ipv41, IPV4_LENGTH_BYTES);
    memcpy(ipv42copy, ipv42, IPV4_LENGTH_BYTES);
    memcpy(mac1copy,  mac1,  MAC_LENGTH_BYTES);
    memcpy(mac2copy,  mac2,  MAC_LENGTH_BYTES);

    ArpPacketEthernetIpv4 apei1(1, mac1, ipv41, mac2, ipv42);
    MUST_BE_TRUE(apei1.getLengthBytes() == PACKET_LENGTH);

    memset(&ipv41, 99, IPV4_LENGTH_BYTES);
    memset(&ipv42, 99, IPV4_LENGTH_BYTES);
    memset(&mac1,  99, MAC_LENGTH_BYTES);
    memset(&mac2,  99, MAC_LENGTH_BYTES);

    unsigned char raw_apei1[PACKET_LENGTH];
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
    offset += fieldPull(raw_apei1 + offset, oper);

    MUST_BE_TRUE(htype == ArpPacketEthernetIpv4::HTYPE);
    MUST_BE_TRUE(ptype == ArpPacketEthernetIpv4::PTYPE);
    MUST_BE_TRUE(hlen  == ArpPacketEthernetIpv4::HLEN);
    MUST_BE_TRUE(plen  == ArpPacketEthernetIpv4::PLEN);
    MUST_BE_TRUE(oper  == 1);

    MUST_BE_TRUE(memcmp(raw_apei1 + offset, mac1copy, MAC_LENGTH_BYTES) == 0);
    offset += MAC_LENGTH_BYTES;

    MUST_BE_TRUE(memcmp(raw_apei1 + offset, ipv41copy, IPV4_LENGTH_BYTES) == 0);
    offset += IPV4_LENGTH_BYTES;

    MUST_BE_TRUE(memcmp(raw_apei1 + offset, mac2copy, MAC_LENGTH_BYTES) == 0);
    offset += MAC_LENGTH_BYTES;

    MUST_BE_TRUE(memcmp(raw_apei1 + offset, ipv42copy, IPV4_LENGTH_BYTES) == 0);

    ArpPacketEthernetIpv4 apei2(raw_apei1);
    MUST_BE_TRUE(apei2.getOper() == 1);
    MUST_BE_TRUE(*apei2.getSha() == MacAddress("01:01:01:01:01:01"));
    MUST_BE_TRUE(*apei2.getSpa() == Ipv4Address("1.1.1.1"));
    MUST_BE_TRUE(*apei2.getTha() == MacAddress("02:02:02:02:02:02"));
    MUST_BE_TRUE(*apei2.getTpa() == Ipv4Address("2.2.2.2"));

    return Test::PASSED;
}

//==============================================================================
template <class T>
unsigned int fieldPull(unsigned char* buffer, T& destination)
{
    memcpy(&destination, buffer, sizeof(T));
    return sizeof(T);
}
