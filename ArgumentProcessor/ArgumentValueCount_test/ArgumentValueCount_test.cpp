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
    ArgumentValueCount argument_value(0);

    MUST_BE_TRUE(!argument_value.isSet());

    argument_value.update();

    MUST_BE_TRUE(argument_value.isSet());
    MUST_BE_TRUE(argument_value.getCount() == 1);

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentValueCount_test::OperatorLessThan::body()
{
    ArgumentValueCount arg0(0);
    ArgumentValueCount arg1(1);

    MUST_BE_TRUE(arg0 < arg1);
    MUST_BE_TRUE(!(arg1 < arg0));
    MUST_BE_TRUE(!(arg0 < arg0));

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentValueCount_test::OperatorGreaterThan::body()
{
    ArgumentValueCount arg0(0);
    ArgumentValueCount arg1(1);

    MUST_BE_TRUE(arg1 > arg0);
    MUST_BE_TRUE(!(arg0 > arg1));
    MUST_BE_TRUE(!(arg0 > arg0));

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentValueCount_test::OperatorLessThanOrEqualTo::body()
{
    ArgumentValueCount arg0(0);
    ArgumentValueCount arg1(1);

    MUST_BE_TRUE(arg0 <= arg1);
    MUST_BE_TRUE(!(arg1 <= arg0));
    MUST_BE_TRUE(arg0 <= arg0);

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentValueCount_test::OperatorGreaterThanOrEqualTo::body()
{
    ArgumentValueCount arg0(0);
    ArgumentValueCount arg1(1);

    MUST_BE_TRUE(arg1 >= arg0);
    MUST_BE_TRUE(!(arg0 >= arg1));
    MUST_BE_TRUE(arg0 >= arg0);

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentValueCount_test::OperatorEquality::body()
{
    ArgumentValueCount arg0(0);
    ArgumentValueCount arg1(1);

    MUST_BE_TRUE(arg0 == arg0);
    MUST_BE_TRUE(!(arg0 == arg1));

    return Test::PASSED;
}

//==============================================================================
Test::Result ArgumentValueCount_test::OperatorNotEqual::body()
{
    ArgumentValueCount arg0(0);
    ArgumentValueCount arg1(1);

    MUST_BE_TRUE(arg0 != arg1);
    MUST_BE_TRUE(!(arg0 != arg0));

    return Test::PASSED;
}
