#if !defined CONFIGURATION_ARGUMENT_PROCESSOR_TEST
#define CONFIGURATION_ARGUMENT_PROCESSOR_TEST

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

namespace Configuration
{

    TEST_CASES_BEGIN(ArgumentProcessor_test)

        TEST(RegisterPositionalArgument)
        TEST(RegisterOptionalArgument)

        TEST_CASES_BEGIN(Process)

            TEST(PositionalArgument)
            TEST(OptionalArgument)
            TEST(OptionalCountingArgument)
            TEST(Combined)

        TEST_CASES_END(Process)

        TEST(IsRegistered)

    TEST_CASES_END(ArgumentProcessor_test)

}

#endif
