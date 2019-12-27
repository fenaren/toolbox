#include "ArgumentValue_test.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(ArgumentValue_test);

//==============================================================================
void ArgumentValue_test::addTestCases()
{
    ADD_TEST_CASE(Stub);
}

//==============================================================================
Test::Result ArgumentValue_test::Stub::body()
{
    return Test::PASSED;
}
