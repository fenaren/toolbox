#include "EthernetIIHeader.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

TRIVIAL_TEST(EthernetIIHeader_test);

//==============================================================================
Test::Result EthernetIIHeader_test::run()
{
    EthernetIIHeader eth_header(EthernetIIHeader::IPV4);
    MUST_BE_TRUE(eth_header.getLengthBytes() == EthernetIIHeader::LENGTH_BYTES);

    unsigned char eth_header_raw[EthernetIIHeader::LENGTH_BYTES];
    eth_header.writeRaw(eth_header_raw, misc::BIG_ENDIAN);

    // Make sure the Ethertype is always written big endian; 0x0800 is the
    // Ethertype for IPv4
    MUST_BE_TRUE(eth_header_raw[EthernetIIHeader::LENGTH_BYTES - 2] == 0x08);
    MUST_BE_TRUE(eth_header_raw[EthernetIIHeader::LENGTH_BYTES - 1] == 0x00);

    return Test::PASSED;
}
