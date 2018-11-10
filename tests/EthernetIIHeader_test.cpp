#include "EthernetIIHeader_test.hpp"

#include "EthernetIIHeader.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

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
    EthernetIIHeader eth_header;
    MUST_BE_TRUE(eth_header.getLengthBytes() == 14);
    return Test::PASSED;
}
