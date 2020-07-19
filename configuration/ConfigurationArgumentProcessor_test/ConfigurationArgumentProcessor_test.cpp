#include <iostream>
#include <iterator>
#include <string>

#include "ConfigurationArgumentProcessor_test.hpp"

#include "ConfigurationArgumentProcessor.hpp"
#include "ConfigurationSimpleParameter.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Configuration::ArgumentProcessor_test);

//=============================================================================================
void Configuration::ArgumentProcessor_test::addTestCases()
{
    ADD_TEST_CASE(RegisterPositionalArgument);
    ADD_TEST_CASE(RegisterOptionalArgument);
    ADD_TEST_CASE(Process);
    ADD_TEST_CASE(IsRegistered);
}

//=============================================================================================
void Configuration::ArgumentProcessor_test::Process::addTestCases()
{
    ADD_TEST_CASE(PositionalArgument);
    ADD_TEST_CASE(OptionalArgument);
    ADD_TEST_CASE(OptionalCountingArgument);
    ADD_TEST_CASE(Combined);
}

//=============================================================================================
Test::Result Configuration::ArgumentProcessor_test::RegisterPositionalArgument::body()
{
    ArgumentProcessor argument_processor;

    SimpleParameter<int> cv0(0);
    SimpleParameter<int> cv1(1);

    // Iterator should indicate that every positional argument (none at this point) has been
    // processed
    MUST_BE_TRUE(argument_processor.next_positional_argument ==
                 argument_processor.positional_arguments.end());

    argument_processor.registerPositionalArgument(&cv0);

    // There should now be one argument, since we just pushed one
    MUST_BE_TRUE(argument_processor.positional_arguments.size() == 1);

    // Iterator should now indicate the next argument to process is the one we just pushed
    MUST_BE_TRUE(argument_processor.next_positional_argument ==
                 argument_processor.positional_arguments.begin());

    argument_processor.registerPositionalArgument(&cv1);

    // Now there are two, since we just pushed another
    MUST_BE_TRUE(argument_processor.positional_arguments.size() == 2);

    // We haven't processed anything so the next argument to be processed is still this one
    MUST_BE_TRUE(argument_processor.next_positional_argument ==
                 argument_processor.positional_arguments.begin());

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::ArgumentProcessor_test::RegisterOptionalArgument::body()
{
    ArgumentProcessor argument_processor;

    // Optional argument list should be empty since we haven't registered anything yet.
    MUST_BE_TRUE(argument_processor.optional_arguments.empty());

    SimpleParameter<std::string> cv0;
    argument_processor.registerOptionalArgument(&cv0, {"badflag"});

    // Size should be one since we've registered exactly one argument.
    MUST_BE_TRUE(argument_processor.optional_arguments.size() == 1);

    // We aren't processing anything yet.
    MUST_BE_TRUE(argument_processor.current_optional_argument ==
                 argument_processor.optional_arguments.end());

    // We should be storing a pointer to the av0 argument in the optional arguments map
    // associated with the flag we provided to registerOptionalArgument().
    MUST_BE_TRUE(argument_processor.optional_arguments["badflag"] == &cv0);

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::ArgumentProcessor_test::Process::PositionalArgument::body()
{
    ArgumentProcessor argument_processor;

    // No arguments registered, so list should be empty.
    MUST_BE_TRUE(argument_processor.positional_arguments.size() == 0);

    SimpleParameter<int> cv0;
    argument_processor.registerPositionalArgument(&cv0);

    // One argument registered, so list should be of size 1.
    MUST_BE_TRUE(argument_processor.positional_arguments.size() == 1);

    // ArgumentProcessor should convert this into an int for us
    argument_processor.process("12");

    // See that we actually did get the value back as an int of the correct value.
    MUST_BE_TRUE(cv0.getValue() == 12);

    // Also check that we're done processing positional arguments.
    MUST_BE_TRUE(argument_processor.next_positional_argument ==
                 argument_processor.positional_arguments.end());

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::ArgumentProcessor_test::Process::OptionalArgument::body()
{
    ArgumentProcessor argument_processor;

    // No arguments registered yet, size should be 0.
    MUST_BE_TRUE(argument_processor.optional_arguments.size() == 0);

    SimpleParameter<int> cv0;
    argument_processor.registerOptionalArgument(&cv0, {"-a"});

    // Do this one with the version of process() that accepts a list of strings.
    argument_processor.process(std::list<std::string>({"-a", "12"}));

    // Check for the correct value using the equality operator.
    MUST_BE_TRUE(cv0 == 12);

    // We should be done processing.
    MUST_BE_TRUE(argument_processor.current_optional_argument ==
                 argument_processor.optional_arguments.end());

    return Test::PASSED;
}

//=============================================================================================
Test::Result
Configuration::ArgumentProcessor_test::Process::OptionalCountingArgument::body()
{
    ArgumentProcessor argument_processor;

    // No arguments registered yet, size should be 0.
    MUST_BE_TRUE(argument_processor.optional_arguments.size() == 0);

    SimpleParameter<unsigned int> cv0;
    SimpleParameter<unsigned int> cv1;
    argument_processor.registerOptionalCountingArgument(&cv0, {"-a"});
    argument_processor.registerOptionalCountingArgument(&cv1, {"-b"});

    // Do this one with the version of process() that accepts a list of strings.
    argument_processor.process(std::list<std::string>({"-a", "-b", "-a"}));

    // Check for the correct value using the equality operator.
    MUST_BE_TRUE(cv0 == 2);
    MUST_BE_TRUE(cv1 == 1);

    // We should be done processing.
    MUST_BE_TRUE(argument_processor.current_optional_argument ==
                 argument_processor.optional_arguments.end());

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::ArgumentProcessor_test::Process::Combined::body()
{
    ArgumentProcessor argument_processor;

    // No arguments registered, size of both lists should be 0.
    MUST_BE_TRUE(argument_processor.positional_arguments.size() == 0);
    MUST_BE_TRUE(argument_processor.optional_arguments.size() == 0);

    // There should be no positional arguments to process.
    MUST_BE_TRUE(argument_processor.next_positional_argument ==
                 argument_processor.positional_arguments.end());

    SimpleParameter<int> cv0;
    SimpleParameter<int> cv1;

    argument_processor.registerOptionalArgument(&cv1, {"--wtf"});
    argument_processor.registerPositionalArgument(&cv0);

    // We just registered one positional argument, and we should be set to process that one
    // next.
    MUST_BE_TRUE(argument_processor.positional_arguments.size() == 1);
    MUST_BE_TRUE(argument_processor.next_positional_argument ==
                 argument_processor.positional_arguments.begin());

    // We just registered one optional argument.
    MUST_BE_TRUE(argument_processor.optional_arguments.size() == 1);

    // Process using the list version of process()
    argument_processor.process(
        std::list<std::string>({"--wtf", "12", "34"}));

    // Check for the correct values.
    MUST_BE_TRUE(cv0.getValue() == 34);
    MUST_BE_TRUE(cv1.getValue() == 12);

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::ArgumentProcessor_test::IsRegistered::body()
{
    ArgumentProcessor argument_processor;

    SimpleParameter<int> cv0;
    SimpleParameter<int> cv1;
    SimpleParameter<unsigned int> cv2;

    argument_processor.registerPositionalArgument(&cv0);
    argument_processor.registerOptionalArgument(
        &cv1, std::unordered_set<std::string>({"asdf"}));
    argument_processor.registerOptionalCountingArgument(
        &cv2, std::unordered_set<std::string>({"gh"}));

    bool exception_caught = false;
    try
    {
        argument_processor.registerPositionalArgument(&cv0);
    }
    catch (std::runtime_error& ex)
    {
        exception_caught = true;
    }
    MUST_BE_TRUE(exception_caught);

    exception_caught = false;
    try
    {
        argument_processor.registerOptionalArgument(
            &cv1, std::unordered_set<std::string>({"eeee"}));
    }
    catch (std::runtime_error& ex)
    {
        exception_caught = true;
    }
    MUST_BE_TRUE(exception_caught);

    exception_caught = false;
    try
    {
        argument_processor.registerOptionalCountingArgument(
            &cv2, std::unordered_set<std::string>({"wwww"}));
    }
    catch (std::runtime_error& ex)
    {
        exception_caught = true;
    }
    MUST_BE_TRUE(exception_caught);

    return Test::PASSED;
}
