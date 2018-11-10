#include "EthernetIIHeader_test.hpp"

#include "EthernetIIHeader.hpp"
#include "Ethertype.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

TEST_PROGRAM_MAIN(EthernetIIHeader_test);

//==============================================================================
EthernetIIHeader_test::EthernetIIHeader_test()
{
}

//==============================================================================
EthernetIIHeader_test::~EthernetIIHeader_test()
{
}

//==============================================================================
Test::Result EthernetIIHeader_test::run()
{
    EthernetIIHeader eth_header(Ethertype::IPV4);
    MUST_BE_TRUE(eth_header.getLengthBytes() == 14);

    unsigned char eth_header_raw[14];
    eth_header.writeRaw(eth_header_raw, misc::BIG_ENDIAN);

    // Make sure the Ethertype is always written big endian; 0x0800 is the
    // Ethertype for IPv4
    MUST_BE_TRUE(eth_header_raw[12] == 0x08);
    MUST_BE_TRUE(eth_header_raw[13] == 0x00);

    return Test::PASSED;
}
