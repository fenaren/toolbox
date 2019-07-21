#if !defined MAC_ADDRESS_TEST
#define MAC_ADDRESS_TEST

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(MacAddress_test)

    TEST_CASES_BEGIN(Operators)

        TEST(EqualTo)
        TEST(NotEqualTo)

    TEST_CASES_END(Operators)

TEST_CASES_END(MacAddress_test)

#endif
