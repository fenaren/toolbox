#include "ArgumentProcessor_test.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(ArgumentProcessor_test);

//==============================================================================
void ArgumentProcessor_test::addTestCases()
{
    ADD_TEST_CASE(Stub);
}

//==============================================================================
Test::Result ArgumentProcessor_test::Stub::body()
{
    return Test::PASSED;
}
