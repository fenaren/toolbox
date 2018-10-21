#include <iostream>
#include <stdexcept>

#include "ArpPacket_test.hpp"

#include "ArpPacket.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(ArpPacket_test);

//==============================================================================
ArpPacket_test::ArpPacket_test()
{
}

//==============================================================================
ArpPacket_test::~ArpPacket_test()
{
}

//==============================================================================
Test::Result ArpPacket_test::run()
{
    const unsigned int HLEN  = 6;
    const unsigned int PLEN4 = 4;
    const unsigned int PLEN6 = 16;
    const unsigned int HTYPE = 1;
    const unsigned int PTYPE = 2048;
    const unsigned int OPER  = 42;

    unsigned char mac1[] = {6, 5, 4, 3, 2, 1};
    unsigned char mac2[] = {9, 8, 7, 6, 5, 4};

    unsigned char ip41[] = {1, 2, 3, 4};
    unsigned char ip42[] = {5, 6, 7, 8};

    unsigned char ip61[] =
        {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16};
    unsigned char ip62[] =
        {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

    NetworkAddress namac_good(6);
    NetworkAddress namac_bad(8);
    NetworkAddress na4_good(4);
    NetworkAddress na4_bad(5);

    // Ethernet and IPv4
    ArpPacket arp_packet1(
        HTYPE, PTYPE, HLEN, PLEN4, OPER, mac1, ip41, mac2, ip42);
    MUST_BE_TRUE(arp_packet1.getLengthBytes() == 28);

    // Bad length sha
    bool exception_caught = false;
    try
    {
        ArpPacket arp_packet1(HTYPE,
                              PTYPE,
                              HLEN,
                              PLEN4,
                              OPER,
                              namac_bad,
                              na4_good,
                              namac_good,
                              na4_good);
    }
    catch (std::runtime_error& ex)
    {
        exception_caught = true;
        std::cout << ex.what() << "\n";
    }
    MUST_BE_TRUE(exception_caught);

    // Bad length spa
    exception_caught = false;
    try
    {
        ArpPacket arp_packet1(HTYPE,
                              PTYPE,
                              HLEN,
                              PLEN4,
                              OPER,
                              namac_good,
                              na4_bad,
                              namac_good,
                              na4_good);
    }
    catch (std::runtime_error& ex)
    {
        exception_caught = true;
        std::cout << ex.what() << "\n";
    }
    MUST_BE_TRUE(exception_caught);

    // Bad length tha
    exception_caught = false;
    try
    {
        ArpPacket arp_packet1(HTYPE,
                              PTYPE,
                              HLEN,
                              PLEN4,
                              OPER,
                              namac_good,
                              na4_good,
                              namac_bad,
                              na4_good);
    }
    catch (std::runtime_error& ex)
    {
        exception_caught = true;
        std::cout << ex.what() << "\n";
    }
    MUST_BE_TRUE(exception_caught);

    // Bad length tpa
    exception_caught = false;
    try
    {
        ArpPacket arp_packet1(HTYPE,
                              PTYPE,
                              HLEN,
                              PLEN4,
                              OPER,
                              namac_good,
                              na4_good,
                              namac_good,
                              na4_bad);
    }
    catch (std::runtime_error& ex)
    {
        exception_caught = true;
        std::cout << ex.what() << "\n";
    }
    MUST_BE_TRUE(exception_caught);

    // Ethernet and IPv6
    ArpPacket arp_packet2(
        HTYPE, PTYPE, HLEN, PLEN6, OPER, mac1, ip61, mac2, ip62);
    MUST_BE_TRUE(arp_packet2.getLengthBytes() == 52);

    return Test::PASSED;
}
