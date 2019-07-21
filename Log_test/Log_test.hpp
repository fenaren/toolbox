#if !defined LOG_TEST
#define LOG_TEST

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(Log_test)

    TEST_CASES_BEGIN(GreenwichMeanTime)

        TEST(Normal)
        TEST(Warning)
        TEST(Error)

    TEST_CASES_END(GreenwichMeanTime)

    TEST_CASES_BEGIN(LocalTime)

        TEST(Normal)
        TEST(Warning)
        TEST(Error)

    TEST_CASES_END(LocalTime)

TEST_CASES_END(Log_test)

#endif
