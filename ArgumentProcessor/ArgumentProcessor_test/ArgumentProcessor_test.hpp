#if !defined ARGUMENT_PROCESSOR_TEST
#define ARGUMENT_PROCESSOR_TEST

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(ArgumentProcessor_test)

    TEST_CASES_BEGIN(RegisterPositionalArgument)

        TEST(Case1)

    TEST_CASES_END(RegisterPositionalArgument)

    TEST_CASES_BEGIN(RegisterOptionalArgument)

        TEST(Case1)

    TEST_CASES_END(RegisterOptionalArgument)

    TEST_CASES_BEGIN(Process)

         TEST(Case1)

    TEST_CASES_END(Process)

TEST_CASES_END(ArgumentProcessor_test)

#endif
