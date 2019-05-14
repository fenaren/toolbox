#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(PosixTimespec_test)

    TEST(OperatorAddition)
    TEST(OperatorSubtraction)
    TEST(OperatorGreaterThan)
    TEST(OperatorGreaterThanEqualTo)
    TEST(OperatorLessThan)
    TEST(OperatorLessThanEqualTo)
    TEST(BreakMeUp)

TEST_CASES_END(PosixTimespec_test)

enum Greater
{
    LHS,
    RHS,
    EQUAL
};

struct TimespecGtlt
{
    timespec lhs;
    timespec rhs;
    Greater  greater;
};

struct TimespecTuple
{
    timespec lhs;
    timespec rhs;
    timespec result;
};
