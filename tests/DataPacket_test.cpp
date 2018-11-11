#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_HEADER(DataPacket_test_case1);
TEST_HEADER(DataPacket_test_case2);
TEST_HEADER(DataPacket_test_case3);

TRIVIAL_TEST_CASES(DataPacket_test);

//==============================================================================
void DataPacket_test::addTestCases()
{
    addTestCase(new DataPacket_test_case1());
    addTestCase(new DataPacket_test_case2());
    addTestCase(new DataPacket_test_case3());
}
