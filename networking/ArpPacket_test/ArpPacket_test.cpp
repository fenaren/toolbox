#include <iostream>
#include <stdexcept>

#include "ArpPacket.hpp"

#include "RawDataField.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_PROGRAM_BEGIN(ArpPacket_test)
TEST(EthernetIpv4)
TEST(EthernetIpv6)
TEST_CASES_PROGRAM_END(ArpPacket_test)

const unsigned int HLEN  = 6;
const unsigned int PLEN4 = 4;
const unsigned int PLEN6 = 16;
const unsigned int HTYPE = 1;
const unsigned int PTYPE = 2048;
const unsigned int OPER  = 42;

const unsigned char mac1[] = {6, 5, 4, 3, 2, 1};
const unsigned char mac2[] = {9, 8, 7, 6, 5, 4};
const unsigned char ip41[] = {1, 2, 3, 4};
const unsigned char ip42[] = {5, 6, 7, 8};
const unsigned char ip61[] =
    {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16};
const unsigned char ip62[] =
    {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

bool isLengthBad(const RawDataField& bf1,
                 const RawDataField& bf2,
                 const RawDataField& bf3,
                 const RawDataField& bf4);

//==============================================================================
void ArpPacket_test::addTestCases()
{
    addTestCase(new EthernetIpv4());
}

//==============================================================================
Test::Result ArpPacket_test::EthernetIpv4::body()
{
    ArpPacket arp_packet(
        HTYPE, PTYPE, HLEN, PLEN4, OPER, mac1, ip41, mac2, ip42);
    MUST_BE_TRUE(arp_packet.getLengthBytes() == 28);

    return Test::PASSED;
}

//==============================================================================
Test::Result ArpPacket_test::EthernetIpv6::body()
{
    ArpPacket arp_packet(
        HTYPE, PTYPE, HLEN, PLEN6, OPER, mac1, ip61, mac2, ip62);
    MUST_BE_TRUE(arp_packet.getLengthBytes() == 52);

    return Test::PASSED;
}

/*
//==============================================================================
Test::Result ArpPacket_test::body()
{
    RawDataField bfmac_good(6, misc::BYTES);
    RawDataField bfmac_bad(8, misc::BYTES);
    RawDataField bf4_good(4, misc::BYTES);
    RawDataField bf4_bad(5, misc::BYTES);

    // Bad length sha
    MUST_BE_TRUE(isLengthBad(bfmac_bad, bf4_good, bfmac_good, bf4_good));

    // Bad length spa
    MUST_BE_TRUE(isLengthBad(bfmac_good, bf4_bad, bfmac_good, bf4_good));

    // Bad length tha
    MUST_BE_TRUE(isLengthBad(bfmac_good, bf4_good, bfmac_bad, bf4_good));

    // Bad length tpa
    MUST_BE_TRUE(isLengthBad(bfmac_good, bf4_good, bfmac_good, bf4_bad));

    return Test::PASSED;
}
*/

//==============================================================================
bool isLengthBad(const RawDataField& bf1,
                 const RawDataField& bf2,
                 const RawDataField& bf3,
                 const RawDataField& bf4)
{
    bool exception_caught = false;

    try
    {
        ArpPacket arp_packet(
            HTYPE, PTYPE, HLEN, PLEN4, OPER, bf1, bf2, bf3, bf4);
    }
    catch (std::runtime_error& ex)
    {
        exception_caught = true;
        std::cout << ex.what() << "\n";
    }

    return exception_caught;
}
