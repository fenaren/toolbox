#if !defined POSIX_TIMESPEC_TEST
#define POSIX_TIMESPEC_TEST

#include <time.h>

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(PosixTimespec_test)

    TEST_CASES_BEGIN(Operators)

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

        TEST_CASES_BEGIN(GreaterThan)

            TEST(Case1)
            TEST(Case2)
            TEST(Case3)

        TEST_CASES_END(GreaterThan)

        TEST_CASES_BEGIN(GreaterThanOrEqualTo)

            TEST(Case1)
            TEST(Case2)
            TEST(Case3)

        TEST_CASES_END(GreaterThanOrEqualTo)

        TEST_CASES_BEGIN(LessThan)

            TEST(Case1)
            TEST(Case2)
            TEST(Case3)

        TEST_CASES_END(LessThan)

        TEST_CASES_BEGIN(LessThanOrEqualTo)

            TEST(Case1)
            TEST(Case2)
            TEST(Case3)

        TEST_CASES_END(LessThanOrEqualTo)

        enum ArithmeticOperation
        {
            ADDITION,
            SUBTRACTION
        };

        enum ComparisonOperation
        {
            GREATER_THAN,
            GREATER_THAN_OR_EQUAL_TO,
            LESS_THAN,
            LESS_THAN_OR_EQUAL_TO
        };

        // For binary arithmetic operators like addition and subtraction
        static Test::Result operatorTest(
            time_t              lhs_tv_sec,
            long                lhs_tv_nsec,
            time_t              rhs_tv_sec,
            long                rhs_tv_nsec,
            time_t              result_tv_sec,
            long                result_tv_nsec,
            ArithmeticOperation operation);

        // For binary comparison operators like greater than and less than
        static Test::Result operatorTest(time_t              lhs_tv_sec,
                                         long                lhs_tv_nsec,
                                         time_t              rhs_tv_sec,
                                         long                rhs_tv_nsec,
                                         bool                result,
                                         ComparisonOperation operation);

    TEST_CASES_END(Operators)

TEST_CASES_END(PosixTimespec_test)

#endif
