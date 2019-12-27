#include "ArgumentValueList_test.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(ArgumentValueList_test);

//==============================================================================
void ArgumentValueList_test::addTestCases()
{
    ADD_TEST_CASE(Stub);
}

//==============================================================================
Test::Result ArgumentValueList_test::Stub::body()
{
    return Test::PASSED;
}
