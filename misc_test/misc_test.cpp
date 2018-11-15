#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_HEADER(misc_test_case1);

TRIVIAL_TEST_CASES(misc_test);

//==============================================================================
void misc_test::addTestCases()
{
    addTestCase(new misc_test_case1());
}
