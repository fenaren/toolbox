#if !defined ARP_PACKET_TEST
#define ARP_PACKET_TEST

#include "RawDataField.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(ArpPacket_test)

    TEST(Constructor_BadLengthSha)
    TEST(Constructor_BadLengthSpa)
    TEST(Constructor_BadLengthTha)
    TEST(Constructor_BadLengthTpa)
    TEST(Length_EthernetIpv4)
    TEST(Length_EthernetIpv6)

TEST_CASES_END(ArpPacket_test)

bool isLengthBad(const RawDataField& bf1,
                 const RawDataField& bf2,
                 const RawDataField& bf3,
                 const RawDataField& bf4);

#endif
