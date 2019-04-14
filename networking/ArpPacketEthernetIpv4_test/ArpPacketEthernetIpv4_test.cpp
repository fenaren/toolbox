#include <cstdint>
#include <cstring>
#include <iostream>

#include "ArpPacketEthernetIpv4.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

TEST_CASES_PROGRAM_BEGIN(ArpPacketEthernetIpv4_test)
TEST(Length)
TEST(WriteRaw)
TEST(Constructor_ReadRaw)
TEST_CASES_PROGRAM_END(ArpPacketEthernetIpv4_test)

// ARP packets carrying IPv4 and Ethernet addresses are exactly this length
const unsigned int PACKET_LENGTH = 28;

const unsigned int MAC_LENGTH_BYTES  = 6;
const unsigned int IPV4_LENGTH_BYTES = 4;

template <class T>
unsigned int fieldPull(unsigned char* buffer, T& destination);

//==============================================================================
void ArpPacketEthernetIpv4_test::addTestCases()
{
    addTestCase(new Length());
    addTestCase(new WriteRaw());
    addTestCase(new Constructor_ReadRaw());
}

//==============================================================================
Test::Result ArpPacketEthernetIpv4_test::Length::body()
{
    unsigned char ipv41[IPV4_LENGTH_BYTES];
    unsigned char ipv42[IPV4_LENGTH_BYTES];
    unsigned char mac1[MAC_LENGTH_BYTES];
    unsigned char mac2[MAC_LENGTH_BYTES];

    ArpPacketEthernetIpv4 apei(1, mac1, ipv41, mac2, ipv42);
    MUST_BE_TRUE(apei.getLengthBytes() == PACKET_LENGTH);

    return Test::PASSED;
}

//==============================================================================
Test::Result ArpPacketEthernetIpv4_test::WriteRaw::body()
{
    unsigned char ipv41[] = {1, 1, 1, 1};
    unsigned char ipv42[] = {2, 2, 2, 2};
    unsigned char mac1[]  = {1, 1, 1, 1, 1, 1};
    unsigned char mac2[]  = {2, 2, 2, 2, 2, 2};

    ArpPacketEthernetIpv4 apei(1, mac1, ipv41, mac2, ipv42);

    unsigned char ipv41copy[IPV4_LENGTH_BYTES];
    unsigned char ipv42copy[IPV4_LENGTH_BYTES];
    unsigned char mac1copy[MAC_LENGTH_BYTES];
    unsigned char mac2copy[MAC_LENGTH_BYTES];

    memcpy(ipv41copy, ipv41, IPV4_LENGTH_BYTES);
    memcpy(ipv42copy, ipv42, IPV4_LENGTH_BYTES);
    memcpy(mac1copy,  mac1,  MAC_LENGTH_BYTES);
    memcpy(mac2copy,  mac2,  MAC_LENGTH_BYTES);

    memset(&ipv41, 99, IPV4_LENGTH_BYTES);
    memset(&ipv42, 99, IPV4_LENGTH_BYTES);
    memset(&mac1,  99, MAC_LENGTH_BYTES);
    memset(&mac2,  99, MAC_LENGTH_BYTES);

    unsigned char raw_apei[PACKET_LENGTH];
    apei.DataField::writeRaw(raw_apei);

    std::uint16_t htype;
    std::uint16_t ptype;
    std::uint8_t  hlen;
    std::uint8_t  plen;
    std::uint16_t oper;

    unsigned int offset = 0;
    offset += fieldPull(raw_apei + offset, htype);
    offset += fieldPull(raw_apei + offset, ptype);
    offset += fieldPull(raw_apei + offset, hlen);
    offset += fieldPull(raw_apei + offset, plen);
    offset += fieldPull(raw_apei + offset, oper);

    MUST_BE_TRUE(htype == ArpPacketEthernetIpv4::HTYPE);
    MUST_BE_TRUE(ptype == ArpPacketEthernetIpv4::PTYPE);
    MUST_BE_TRUE(hlen  == ArpPacketEthernetIpv4::HLEN);
    MUST_BE_TRUE(plen  == ArpPacketEthernetIpv4::PLEN);
    MUST_BE_TRUE(oper  == 1);

    MUST_BE_TRUE(memcmp(raw_apei + offset, mac1copy, MAC_LENGTH_BYTES) == 0);
    offset += MAC_LENGTH_BYTES;

    MUST_BE_TRUE(memcmp(raw_apei + offset, ipv41copy, IPV4_LENGTH_BYTES) == 0);
    offset += IPV4_LENGTH_BYTES;

    MUST_BE_TRUE(memcmp(raw_apei + offset, mac2copy, MAC_LENGTH_BYTES) == 0);
    offset += MAC_LENGTH_BYTES;

    MUST_BE_TRUE(memcmp(raw_apei + offset, ipv42copy, IPV4_LENGTH_BYTES) == 0);

    return Test::PASSED;
}

//==============================================================================
Test::Result ArpPacketEthernetIpv4_test::Constructor_ReadRaw::body()
{
    // Copied this from memory after the apei.writeRaw() in the test case above
    const std::uint8_t raw_apei[] =
        {1, 0,
         0, 8,
         6,
         4,
         1, 0,
         1, 1, 1, 1, 1, 1,
         1, 1, 1, 1,
         2, 2, 2, 2, 2, 2,
         2, 2, 2, 2};

    ArpPacketEthernetIpv4 apei(raw_apei, misc::ENDIAN_LITTLE);

    std::cout << "Oper " << apei.getOper() << "\n";
    MUST_BE_TRUE(apei.getOper() == 1);

    MUST_BE_TRUE(*apei.getSha() == MacAddress("01:01:01:01:01:01"));
    MUST_BE_TRUE(*apei.getSpa() == Ipv4Address("1.1.1.1"));
    MUST_BE_TRUE(*apei.getTha() == MacAddress("02:02:02:02:02:02"));
    MUST_BE_TRUE(*apei.getTpa() == Ipv4Address("2.2.2.2"));

    return Test::PASSED;
}

//==============================================================================
template <class T>
unsigned int fieldPull(unsigned char* buffer, T& destination)
{
    memcpy(&destination, buffer, sizeof(T));
    return sizeof(T);
}
