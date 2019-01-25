#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_HEADER(SimpleDataField_test_case1);
TEST_HEADER(SimpleDataField_test_case2);

TRIVIAL_TEST_CASES(SimpleDataField_test);

//==============================================================================
void SimpleDataField_test::addTestCases()
{
    addTestCase(new SimpleDataField_test_case1());
    addTestCase(new SimpleDataField_test_case2());
}
