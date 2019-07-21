#include <iostream>
#include <stdexcept>

#include "ArpPacket_test.hpp"

#include "ArpPacket.hpp"
#include "RawDataField.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

const RawDataField ArpPacket_test::Constructor::bfmac_good(6, misc::BYTES);
const RawDataField ArpPacket_test::Constructor::bfmac_bad(8,  misc::BYTES);
const RawDataField ArpPacket_test::Constructor::bf4_good(4,   misc::BYTES);
const RawDataField ArpPacket_test::Constructor::bf4_bad(5,    misc::BYTES);

const unsigned char ArpPacket_test::Length::mac1[] = {6, 5, 4, 3, 2, 1};
const unsigned char ArpPacket_test::Length::mac2[] = {9, 8, 7, 6, 5, 4};
const unsigned char ArpPacket_test::Length::ip41[] = {1, 2, 3, 4};
const unsigned char ArpPacket_test::Length::ip42[] = {5, 6, 7, 8};
const unsigned char ArpPacket_test::Length::ip61[] =
    {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16};
const unsigned char ArpPacket_test::Length::ip62[] =
    {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

TEST_PROGRAM_MAIN(ArpPacket_test)

//==============================================================================
void ArpPacket_test::addTestCases()
{
    ADD_TEST_CASE(Constructor);
    ADD_TEST_CASE(Length);
}

//==============================================================================
void ArpPacket_test::Constructor::addTestCases()
{
    ADD_TEST_CASE(BadLengthSha);
    ADD_TEST_CASE(BadLengthSpa);
    ADD_TEST_CASE(BadLengthTha);
    ADD_TEST_CASE(BadLengthTpa);
}

//==============================================================================
void ArpPacket_test::Length::addTestCases()
{
    ADD_TEST_CASE(EthernetIpv4);
    ADD_TEST_CASE(EthernetIpv6);
}

//==============================================================================
Test::Result ArpPacket_test::Constructor::BadLengthSha::body()
{
    // Bad length sha
    MUST_BE_TRUE(isLengthBad(bfmac_bad, bf4_good, bfmac_good, bf4_good));
    return Test::PASSED;
}

//==============================================================================
Test::Result ArpPacket_test::Constructor::BadLengthSpa::body()
{
    // Bad length spa
    MUST_BE_TRUE(isLengthBad(bfmac_good, bf4_bad, bfmac_good, bf4_good));
    return Test::PASSED;
}

//==============================================================================
Test::Result ArpPacket_test::Constructor::BadLengthTha::body()
{
    // Bad length tha
    MUST_BE_TRUE(isLengthBad(bfmac_good, bf4_good, bfmac_bad, bf4_good));
    return Test::PASSED;
}

//==============================================================================
Test::Result ArpPacket_test::Constructor::BadLengthTpa::body()
{
    MUST_BE_TRUE(isLengthBad(bfmac_good, bf4_good, bfmac_good, bf4_bad));
    return Test::PASSED;
}

//==============================================================================
Test::Result ArpPacket_test::Length::EthernetIpv4::body()
{
    ArpPacket arp_packet(
        HTYPE, PTYPE, HLEN, PLEN4, OPER, mac1, ip41, mac2, ip42);
    MUST_BE_TRUE(arp_packet.getLengthBytes() == 28);

    return Test::PASSED;
}

//==============================================================================
Test::Result ArpPacket_test::Length::EthernetIpv6::body()
{
    ArpPacket arp_packet(
        HTYPE, PTYPE, HLEN, PLEN6, OPER, mac1, ip61, mac2, ip62);
    MUST_BE_TRUE(arp_packet.getLengthBytes() == 52);

    return Test::PASSED;
}

//==============================================================================
bool ArpPacket_test::Constructor::isLengthBad(const RawDataField& bf1,
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
