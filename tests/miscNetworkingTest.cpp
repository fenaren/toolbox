#include "miscNetworkingTest.hpp"

#include "TestCases.hpp"
#include "TestProgramMain.hpp"
#include "miscNetworkingTest_case1.hpp"
#include "miscNetworkingTest_case2.hpp"

TEST_PROGRAM_MAIN(miscNetworkingTest);

//==============================================================================
miscNetworkingTest::miscNetworkingTest()
{
}

//==============================================================================
miscNetworkingTest::~miscNetworkingTest()
{
}

//==============================================================================
void miscNetworkingTest::addTestCases()
{
    addTestCase(&case1);
    addTestCase(&case2);
}
