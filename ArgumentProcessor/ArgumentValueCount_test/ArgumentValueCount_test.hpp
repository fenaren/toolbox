#if !defined ARGUMENT_VALUE_COUNT_TEST_HPP
#define ARGUMENT_VALUE_COUNT_TEST_HPP

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

#include "ArgumentValueCount.hpp"

TEST_CASES_BEGIN(ArgumentValueCount_test)

    TEST(Update)

    // Relational operators
    TEST(OperatorLessThan)
    TEST(OperatorGreaterThan)
    TEST(OperatorLessThanOrEqualTo)
    TEST(OperatorGreaterThanOrEqualTo)
    TEST(OperatorEquality)
    TEST(OperatorNotEqual)

TEST_CASES_END(ArgumentValueCount_test)

#endif
