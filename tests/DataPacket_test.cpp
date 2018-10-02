#include <iostream>

#include "DataPacket_test.hpp"

#include "DataPacket.hpp"
#include "DataPacket_test1.hpp"
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
    DataPacket_test1 dptest1;

    // The right side of the equality operator represents the known sum total of
    // all the sizes in the packet.  There are five total "leaf" fields of types
    // int, double, and float (3 of these).  The total packet length should
    // equal the sum of these.
    MUST_BE_TRUE(dptest1.getLengthBytes() ==
                 sizeof(int) + sizeof(double) + (3 * sizeof(float)));

    return Test::PASSED;
}
