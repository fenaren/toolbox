#if !defined MISC_NETWORKING_TEST
#define MISC_NETWORKING_TEST

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(miscNetworking_test)

    TEST(GetMacAddress)
    TEST(GetIpv4Address)

TEST_CASES_END(miscNetworking_test)

#endif
