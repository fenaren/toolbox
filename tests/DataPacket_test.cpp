#include "DataPacket_test.hpp"

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
void DataPacket_test::addTestCases()
{
    addTestCase(&dptc1);
    addTestCase(&dptc2);
}
