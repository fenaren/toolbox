#include "miscNetworking_test.hpp"

#include "TestCases.hpp"
#include "TestMacros.hpp"
#include "miscNetworking_test_case1.hpp"
#include "miscNetworking_test_case2.hpp"
#include "miscNetworking_test_case3.hpp"

TEST_PROGRAM_MAIN(miscNetworking_test);

//==============================================================================
miscNetworking_test::miscNetworking_test()
{
}

//==============================================================================
miscNetworking_test::~miscNetworking_test()
{
}

//==============================================================================
void miscNetworking_test::addTestCases()
{
    addTestCase(&case1);
    addTestCase(&case2);
    addTestCase(&case3);
}
