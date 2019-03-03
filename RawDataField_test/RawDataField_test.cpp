#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_HEADER(RawDataField_test_case1);
TEST_HEADER(RawDataField_test_case2);
TEST_HEADER(RawDataField_test_case3);

TRIVIAL_TEST_CASES(RawDataField_test);

//==============================================================================
void RawDataField_test::addTestCases()
{
    addTestCase(new RawDataField_test_case1());
    addTestCase(new RawDataField_test_case2());
    addTestCase(new RawDataField_test_case3());
}
