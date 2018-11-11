#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_HEADER(miscNetworking_test_case1);
TEST_HEADER(miscNetworking_test_case2);

TRIVIAL_TEST_CASES(miscNetworking_test);

//==============================================================================
void miscNetworking_test::addTestCases()
{
    addTestCase(new miscNetworking_test_case1());
    addTestCase(new miscNetworking_test_case2());
}
