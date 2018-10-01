#include <iostream>

#include "DataPacket_test.hpp"

#include "DataPacket.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(DataPacket_test);

//==============================================================================
DataPacket_test::DataPacket_test()
{
}

//==============================================================================
DataPacket_test::~DataPacket_test()
{
}

//==============================================================================
Test::Result DataPacket_test::run()
{
    return Test::PASSED;
}
