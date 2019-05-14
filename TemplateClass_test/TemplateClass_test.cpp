#include "TemplateClass_test.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(TemplateClass_test);

//==============================================================================
void TemplateClass_test::addTestCases()
{
    ADD_TEST_CASE(Stub);
}

//==============================================================================
Test::Result TemplateClass_test::Stub::body()
{
    return Test::PASSED;
}
