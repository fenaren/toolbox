#if !defined POSIX_TIMESPEC_TEST
#define POSIX_TIMESPEC_TEST

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(PosixTimespec_test)

    TEST_CASES_BEGIN(Operator)

        TEST_CASES_BEGIN(Addition)

            TEST(Case1)
            TEST(Case2)
            TEST(Case3)
            TEST(Case4)

        TEST_CASES_END(Addition)

        TEST_CASES_BEGIN(Subtraction)

            TEST(Case1)
            TEST(Case2)
            TEST(Case3)
            TEST(Case4)

        TEST_CASES_END(Subtraction)

        TEST(GreaterThan)
        TEST(GreaterThanEqualTo)
        TEST(LessThan)
        TEST(LessThanEqualTo)

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

    TEST_CASES_END(Operator)

    TEST(BreakMeUp)

TEST_CASES_END(PosixTimespec_test)

#endif
