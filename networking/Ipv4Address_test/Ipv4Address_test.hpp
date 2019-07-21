#if !defined IPV4_ADDRESS_TEST
#define IPV4_ADDRESS_TEST

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(Ipv4Address_test)

    TEST_CASES_BEGIN(Operators)

        TEST(EqualTo)
        TEST(NotEqualTo)

    TEST_CASES_END(Operators)

TEST_CASES_END(Ipv4Address_test)

#endif
