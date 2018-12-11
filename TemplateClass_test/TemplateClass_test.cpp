#include "Test.hpp"
#include "TestMacros.hpp"

// These two use the macros necessary for defining trivial tests and trivial
// test cases, respectively.  If using one of these don't use any other macro
// from TestMacros.hpp.

TRIVIAL_TEST(TemplateClass_test);
//TRIVIAL_TEST_CASES(TemplateClass_test);

// Use TEST_CASES_HEADER if this test is a TestCases, otherwise use
// TEST_HEADER.  Only use if not using one of the TRIVIAL_* macros.

//TEST_HEADER(TemplateClass_test);
//TEST_CASES_HEADER(TemplateClass_test);

// Defines a main() function for this test.  Don't use if this test is used as
// a test case in a separately-defined TestCases-derived class (that test should
// define main()).  Only use if not using one of the TRIVIAL_ macros.

//TEST_PROGRAM_MAIN(TemplateClass_test);

// Defines an empty constructor and destructor.  Only use if not using one of
// the TRIVIAL_* macros.

//TEST_CONSTRUCTOR_DESTRUCTOR(TemplateClass_test);

//==============================================================================
Test::Result TemplateClass_test::body()
{
    return Test::PASSED;
}
