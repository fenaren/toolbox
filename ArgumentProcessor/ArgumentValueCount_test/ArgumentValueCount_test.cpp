#include "ArgumentValueCount_test.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

#include "ArgumentValueCount.hpp"

TEST_PROGRAM_MAIN(ArgumentValueCount_test);

//==============================================================================
void ArgumentValueCount_test::addTestCases()
{
    ADD_TEST_CASE(Stub);
}

//==============================================================================
Test::Result ArgumentValueCount_test::Stub::body()
{
    return Test::PASSED;
}
