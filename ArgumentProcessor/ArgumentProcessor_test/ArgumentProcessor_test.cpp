#include <iostream>
#include <string>

#include "ArgumentProcessor_test.hpp"

#include "ArgumentProcessor.hpp"
#include "ArgumentValue.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(ArgumentProcessor_test);

//==============================================================================
void ArgumentProcessor_test::addTestCases()
{
    ADD_TEST_CASE(RegisterPositionalArgument);
    ADD_TEST_CASE(RegisterOptionalArgument);
    ADD_TEST_CASE(Process);
}

//==============================================================================
void ArgumentProcessor_test::RegisterPositionalArgument::addTestCases()
{
    ADD_TEST_CASE(Case1);
}

//==============================================================================
void ArgumentProcessor_test::RegisterOptionalArgument::addTestCases()
{
    ADD_TEST_CASE(Case1);
}

//==============================================================================
void ArgumentProcessor_test::Process::addTestCases()
{
    ADD_TEST_CASE(Case1);
}

//==============================================================================
Test::Result ArgumentProcessor_test::RegisterPositionalArgument::Case1::body()
{
    ArgumentProcessor argument_processor;

    ArgumentValue<int> av(0);

    argument_processor.registerPositionalArgument(&av);

    MUST_BE_TRUE(!av.isSet());
    MUST_BE_TRUE(!argument_processor.isSatisfied());

    argument_processor.process("12");

    MUST_BE_TRUE(argument_processor.isSatisfied());
    MUST_BE_TRUE(av.isSet());
    MUST_BE_TRUE(av.getValue() == 12);

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentProcessor_test::RegisterOptionalArgument::Case1::body()
{
    ArgumentProcessor argument_processor;
    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentProcessor_test::Process::Case1::body()
{
    ArgumentProcessor argument_processor;
    return Test::PASSED;
}
