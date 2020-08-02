#if !defined CONFIGURATION_LIST_PARAMETER_TEST_HPP
#define CONFIGURATION_LIST_PARAMETER_TEST_HPP

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

namespace Configuration
{
    TEST_CASES_BEGIN(ListParameter_test)

        TEST(FromString)
        TEST(ToString)

    TEST_CASES_END(ListParameter_test)
}

#endif
