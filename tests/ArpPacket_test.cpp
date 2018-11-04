#include <iostream>
#include <stdexcept>

#include "ArpPacket_test.hpp"

#include "ArpPacket.hpp"
#include "NetworkAddress.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(ArpPacket_test);

//==============================================================================
ArpPacket_test::ArpPacket_test() :
    namac_good(6),
    namac_bad(8),
    na4_good(4),
    na4_bad(5)
{
}

//==============================================================================
ArpPacket_test::~ArpPacket_test()
{
}

//==============================================================================
Test::Result ArpPacket_test::run()
{
    unsigned char mac1[] = {6, 5, 4, 3, 2, 1};
    unsigned char mac2[] = {9, 8, 7, 6, 5, 4};
    unsigned char ip41[] = {1, 2, 3, 4};
    unsigned char ip42[] = {5, 6, 7, 8};
    unsigned char ip61[] =
    {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16};
    unsigned char ip62[] =
    {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

    // Ethernet and IPv4
    ArpPacket arp_packet1(
        HTYPE, PTYPE, HLEN, PLEN4, OPER, mac1, ip41, mac2, ip42);
    MUST_BE_TRUE(arp_packet1.getLengthBytes() == 28);

    // Ethernet and IPv6
    ArpPacket arp_packet6(
        HTYPE, PTYPE, HLEN, PLEN6, OPER, mac1, ip61, mac2, ip62);
    MUST_BE_TRUE(arp_packet6.getLengthBytes() == 52);

    // Bad length sha
    MUST_BE_TRUE(isLengthBad(namac_bad, na4_good, namac_good, na4_good));

    // Bad length spa
    MUST_BE_TRUE(isLengthBad(namac_good, na4_bad, namac_good, na4_good));

    // Bad length tha
    MUST_BE_TRUE(isLengthBad(namac_good, na4_good, namac_bad, na4_good));

    // Bad length tpa
    MUST_BE_TRUE(isLengthBad(namac_good, na4_good, namac_good, na4_bad));

    return Test::PASSED;
}

//==============================================================================
bool ArpPacket_test::isLengthBad(const NetworkAddress& na1,
                                 const NetworkAddress& na2,
                                 const NetworkAddress& na3,
                                 const NetworkAddress& na4)
{
    bool exception_caught = false;

    try
    {
        ArpPacket arp_packet(
            HTYPE, PTYPE, HLEN, PLEN4, OPER, na1, na2, na3, na4);
    }
    catch (std::runtime_error& ex)
    {
        exception_caught = true;
        std::cout << ex.what() << "\n";
    }

    return exception_caught;
}
