#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_HEADER(RawDataField_test_case1)
TEST_HEADER(RawDataField_test_case2)
TEST_HEADER(RawDataField_test_case3)

TEST_CASES_HEADER_BEGIN(RawDataField_test)
TEST_DECLARE(RawDataField_test_case1)
TEST_DECLARE(RawDataField_test_case2)
TEST_DECLARE(RawDataField_test_case3)
TEST_CASES_HEADER_END(RawDataField_test)

TEST_CONSTRUCTOR_BEGIN(TestCases, RawDataField_test)
TEST_CONSTRUCT(RawDataField_test_case1)
TEST_CONSTRUCT(RawDataField_test_case2)
TEST_CONSTRUCT(RawDataField_test_case3)
TEST_CONSTRUCTOR_END(RawDataField_test)

TEST_CASES_DESTRUCTOR(RawDataField_test)

TEST_PROGRAM_MAIN(RawDataField_test)

//==============================================================================
void RawDataField_test::addTestCases()
{
    //addTestCase(new RawDataField_test_case1());
    //addTestCase(new RawDataField_test_case2());
    //addTestCase(new RawDataField_test_case3());
}
