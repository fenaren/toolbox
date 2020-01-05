#include <string>

#include "ArgumentValueCount_test.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

#include "ArgumentValueCount.hpp"

TEST_PROGRAM_MAIN(ArgumentValueCount_test);

//==============================================================================
void ArgumentValueCount_test::addTestCases()
{
    ADD_TEST_CASE(Update);

    // Relational operators
    ADD_TEST_CASE(OperatorLessThan);
    ADD_TEST_CASE(OperatorGreaterThan);
    ADD_TEST_CASE(OperatorLessThanOrEqualTo);
    ADD_TEST_CASE(OperatorGreaterThanOrEqualTo);
    ADD_TEST_CASE(OperatorEquality);
    ADD_TEST_CASE(OperatorNotEqual);
}

//==============================================================================
Test::Result ArgumentValueCount_test::Update::body()
{
    ArgumentValueCount argument_value_count(0);

    // New ArgumentValueCounts are supposed to be unset by default.
    MUST_BE_TRUE(!argument_value_count.isSet());

    // Update it; for count arguments this is a trivial operation.
    argument_value_count.update();

    // Now we should be set ...
    MUST_BE_TRUE(argument_value_count.isSet());

    // ... and we should have a count of 1, since we've been updated only once.
    MUST_BE_TRUE(argument_value_count.getCount() == 1);

    argument_value_count.update();

    // Should still be set ...
    MUST_BE_TRUE(argument_value_count.isSet());

    // ... and we should have a count of 2, since we've been updated twice.
    MUST_BE_TRUE(argument_value_count.getCount() == 2);

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentValueCount_test::OperatorLessThan::body()
{
    ArgumentValueCount smaller_arg(0);
    ArgumentValueCount bigger_arg(1);

    MUST_BE_TRUE(  smaller_arg < bigger_arg);
    MUST_BE_TRUE(!(bigger_arg  < smaller_arg));
    MUST_BE_TRUE(!(smaller_arg < smaller_arg));

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentValueCount_test::OperatorGreaterThan::body()
{
    ArgumentValueCount smaller_arg(0);
    ArgumentValueCount bigger_arg(1);

    MUST_BE_TRUE(  bigger_arg  > smaller_arg);
    MUST_BE_TRUE(!(smaller_arg > bigger_arg));
    MUST_BE_TRUE(!(smaller_arg > smaller_arg));

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentValueCount_test::OperatorLessThanOrEqualTo::body()
{
    ArgumentValueCount smaller_arg(0);
    ArgumentValueCount bigger_arg(1);

    MUST_BE_TRUE(  smaller_arg <= bigger_arg);
    MUST_BE_TRUE(!(bigger_arg  <= smaller_arg));
    MUST_BE_TRUE(  smaller_arg <= smaller_arg);

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentValueCount_test::OperatorGreaterThanOrEqualTo::body()
{
    ArgumentValueCount smaller_arg(0);
    ArgumentValueCount bigger_arg(1);

    MUST_BE_TRUE(  bigger_arg  >= smaller_arg);
    MUST_BE_TRUE(!(smaller_arg >= bigger_arg));
    MUST_BE_TRUE(  smaller_arg >= smaller_arg);

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentValueCount_test::OperatorEquality::body()
{
    ArgumentValueCount smaller_arg(0);
    ArgumentValueCount bigger_arg(1);

    MUST_BE_TRUE(  smaller_arg == smaller_arg);
    MUST_BE_TRUE(!(smaller_arg == bigger_arg));

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentValueCount_test::OperatorNotEqual::body()
{
    ArgumentValueCount smaller_arg(0);
    ArgumentValueCount bigger_arg(1);

    MUST_BE_TRUE(  smaller_arg != bigger_arg);
    MUST_BE_TRUE(!(smaller_arg != smaller_arg));

    return Test::PASSED;
}
