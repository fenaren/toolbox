#include "misc_test.hpp"

#include "TestCases.hpp"
#include "TestMacros.hpp"
#include "misc_test_case1.hpp"

TEST_PROGRAM_MAIN(misc_test);

//==============================================================================
misc_test::misc_test()
{
}

//==============================================================================
misc_test::~misc_test()
{
}

//==============================================================================
void misc_test::addTestCases()
{
    addTestCase(&case1);
}
