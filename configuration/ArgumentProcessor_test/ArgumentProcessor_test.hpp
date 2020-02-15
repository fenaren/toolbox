#if !defined ARGUMENT_PROCESSOR_TEST
#define ARGUMENT_PROCESSOR_TEST

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(ArgumentProcessor_test)

    TEST(RegisterPositionalArgument)
    TEST(RegisterOptionalArgument)

    TEST_CASES_BEGIN(Process)

         TEST(PositionalArgument)
         TEST(OptionalArgument)
         TEST(OptionalArgumentCount)
         TEST(Combined)

    TEST_CASES_END(Process)

TEST_CASES_END(ArgumentProcessor_test)

#endif
