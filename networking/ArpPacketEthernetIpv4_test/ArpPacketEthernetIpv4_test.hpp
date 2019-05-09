#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(ArpPacketEthernetIpv4_test)

TEST(Length)
TEST(WriteRaw)
TEST(Constructor_ReadRaw)

TEST_CASES_END(ArpPacketEthernetIpv4_test)

template <class T>
unsigned int fieldPull(unsigned char* buffer, T& destination);
