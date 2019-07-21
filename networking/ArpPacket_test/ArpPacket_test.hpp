#if !defined ARP_PACKET_TEST
#define ARP_PACKET_TEST

#include "RawDataField.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(ArpPacket_test)

    TEST_CASES_BEGIN(Constructor)

        TEST(BadLengthSha)
        TEST(BadLengthSpa)
        TEST(BadLengthTha)
        TEST(BadLengthTpa)

        static const RawDataField bfmac_good;
        static const RawDataField bfmac_bad;
        static const RawDataField bf4_good;
        static const RawDataField bf4_bad;

        static bool isLengthBad(const RawDataField& bf1,
                                const RawDataField& bf2,
                                const RawDataField& bf3,
                                const RawDataField& bf4);

    TEST_CASES_END(Constructor)

    static const unsigned int HLEN  = 6;
    static const unsigned int PLEN4 = 4;
    static const unsigned int PLEN6 = 16;
    static const unsigned int HTYPE = 1;
    static const unsigned int PTYPE = 2048;
    static const unsigned int OPER  = 42;

    TEST_CASES_BEGIN(Length)

        TEST(EthernetIpv4)
        TEST(EthernetIpv6)

        static const unsigned char mac1[HLEN];
        static const unsigned char mac2[HLEN];
        static const unsigned char ip41[PLEN4];
        static const unsigned char ip42[PLEN4];
        static const unsigned char ip61[PLEN6];
        static const unsigned char ip62[PLEN6];

    TEST_CASES_END(Length)

TEST_CASES_END(ArpPacket_test)

#endif
