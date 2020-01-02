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
void ArgumentProcessor_test::Process::addTestCases()
{
    ADD_TEST_CASE(PositionalArgument);
    ADD_TEST_CASE(OptionalArgument);
    ADD_TEST_CASE(Combined);
}

//==============================================================================
Test::Result ArgumentProcessor_test::RegisterPositionalArgument::body()
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
Test::Result ArgumentProcessor_test::RegisterOptionalArgument::body()
{
    ArgumentProcessor argument_processor;

    MUST_BE_TRUE(argument_processor.optional_arguments.empty());

    ArgumentValue<std::string> av0;
    argument_processor.registerOptionalArgument(&av0, {"badflag"});

    MUST_BE_TRUE(argument_processor.optional_arguments.size() == 1);
    MUST_BE_TRUE(argument_processor.current_optional_argument ==
                 argument_processor.optional_arguments.end());

    MUST_BE_TRUE(argument_processor.optional_arguments["badflag"] == &av0);

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentProcessor_test::Process::PositionalArgument::body()
{
    ArgumentProcessor argument_processor;

    MUST_BE_TRUE(argument_processor.positional_arguments.size() == 0);

    ArgumentValue<int> av0;
    argument_processor.registerPositionalArgument(&av0);

    MUST_BE_TRUE(argument_processor.positional_arguments.size() == 1);

    argument_processor.process("12");

    MUST_BE_TRUE(av0.getValue() == 12);
    MUST_BE_TRUE(argument_processor.next_positional_argument ==
                 argument_processor.positional_arguments.end());

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentProcessor_test::Process::OptionalArgument::body()
{
    ArgumentProcessor argument_processor;

    MUST_BE_TRUE(argument_processor.optional_arguments.size() == 0);

    ArgumentValue<int> av0;
    argument_processor.registerOptionalArgument(&av0, {"-a"});
    argument_processor.process(std::list<std::string>({"-a", "12"}));

    MUST_BE_TRUE(av0 == 12);
    MUST_BE_TRUE(argument_processor.current_optional_argument ==
                 argument_processor.optional_arguments.end());

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentProcessor_test::Process::Combined::body()
{
    ArgumentProcessor argument_processor;

    MUST_BE_TRUE(argument_processor.positional_arguments.size() == 0);
    MUST_BE_TRUE(argument_processor.next_positional_argument ==
                 argument_processor.positional_arguments.end());

    MUST_BE_TRUE(argument_processor.optional_arguments.size() == 0);

    ArgumentValue<int> av0;
    ArgumentValue<int> av1;

    argument_processor.registerOptionalArgument(&av1, {"--wtf"});
    argument_processor.registerPositionalArgument(&av0);

    MUST_BE_TRUE(argument_processor.positional_arguments.size() == 1);
    MUST_BE_TRUE(argument_processor.next_positional_argument ==
                 argument_processor.positional_arguments.begin());

    MUST_BE_TRUE(argument_processor.optional_arguments.size() == 1);

    argument_processor.process(std::list<std::string>({"--wtf", "12", "34"}));

    MUST_BE_TRUE(av0.getValue() == 34);
    MUST_BE_TRUE(av1.getValue() == 12);

    return Test::PASSED;
}
