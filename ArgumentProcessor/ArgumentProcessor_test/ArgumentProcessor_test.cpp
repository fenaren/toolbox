#include <iostream>
#include <iterator>
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

    ArgumentValue<int> av0(0);
    ArgumentValue<int> av1(1);

    // Iterator should indicate that every positional argument (none at this
    // point) has been processed
    MUST_BE_TRUE(argument_processor.next_positional_argument ==
                 argument_processor.positional_arguments.end());

    argument_processor.registerPositionalArgument(&av0);

    // There should now be one argument, since we just pushed one
    MUST_BE_TRUE(argument_processor.positional_arguments.size() == 1);

    // Iterator should now indicate the next argument to process is the one we
    // just pushed
    MUST_BE_TRUE(argument_processor.next_positional_argument ==
                 argument_processor.positional_arguments.begin());

    argument_processor.registerPositionalArgument(&av1);

    // Now there are two, since we just pushed another
    MUST_BE_TRUE(argument_processor.positional_arguments.size() == 2);

    // We haven't processed anything so the next argument to be processed is
    // still this one
    MUST_BE_TRUE(argument_processor.next_positional_argument ==
                 argument_processor.positional_arguments.begin());

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
