#include "Configuration_test.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Configuration_test);

//==============================================================================
void Configuration_test::addTestCases()
{
    ADD_TEST_CASE(Stub);
}

//==============================================================================
Test::Result Configuration_test::Stub::body()
{
    return Test::PASSED;
}
