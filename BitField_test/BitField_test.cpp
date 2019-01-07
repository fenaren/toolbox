#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_HEADER(BitField_test_case1);
TEST_HEADER(BitField_test_case2);
TEST_HEADER(BitField_test_case3);

TRIVIAL_TEST_CASES(BitField_test);

//==============================================================================
void BitField_test::addTestCases()
{
    addTestCase(new BitField_test_case1());
    addTestCase(new BitField_test_case2());
    addTestCase(new BitField_test_case3());
}
