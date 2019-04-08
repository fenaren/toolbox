#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_PROGRAM_BEGIN(TemplateClass_test)
TEST(Stub)
TEST_CASES_PROGRAM_END(TemplateClass_test)

//==============================================================================
void TemplateClass_test::addTestCases()
{
    addTestCase(new Stub());
}

//==============================================================================
Test::Result TemplateClass_test::Stub::body()
{
    return Test::PASSED;
}
