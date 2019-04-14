#include "EthernetIIHeader.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

TEST_CASES_PROGRAM_BEGIN(EthernetIIHeader_test)
TEST(Length)
TEST(EthertypeWrite)
TEST_CASES_PROGRAM_END(EthernetIIHeader_test)

//==============================================================================
void EthernetIIHeader_test::addTestCases()
{
    addTestCase(new Length());
    addTestCase(new EthertypeWrite());
}

//==============================================================================
Test::Result EthernetIIHeader_test::Length::body()
{
    EthernetIIHeader eth_header(EthernetIIHeader::IPV4);
    MUST_BE_TRUE(eth_header.getLengthBytes() == EthernetIIHeader::LENGTH_BYTES);

    return Test::PASSED;
}

//==============================================================================
Test::Result EthernetIIHeader_test::EthertypeWrite::body()
{
    EthernetIIHeader eth_header(EthernetIIHeader::IPV4);

    unsigned char eth_header_raw[EthernetIIHeader::LENGTH_BYTES];
    eth_header.writeRaw(eth_header_raw, misc::ENDIAN_BIG);

    // Make sure the Ethertype is always written big endian; 0x0800 is the
    // Ethertype for IPv4
    MUST_BE_TRUE(eth_header_raw[EthernetIIHeader::LENGTH_BYTES - 2] == 0x08);
    MUST_BE_TRUE(eth_header_raw[EthernetIIHeader::LENGTH_BYTES - 1] == 0x00);

    return Test::PASSED;
}
