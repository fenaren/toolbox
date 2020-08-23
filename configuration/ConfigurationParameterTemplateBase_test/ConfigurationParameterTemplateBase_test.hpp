#if !defined CONFIGURATION_PARAMETER_TEMPLATE_BASE_TEST_HPP
#define CONFIGURATION_PARAMETER_TEMPLATE_BASE_TEST_HPP

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

#include "ConfigurationParameterTemplateBase.hpp"

namespace Configuration
{
    TEST_CASES_BEGIN(ParameterTemplateBase_test)

        TEST_CASES_BEGIN(SetValue)

            TEST(Bool)
            TEST(String)
            TEST(Char)
            TEST(Double)
            TEST(Float)
            TEST(Int)
            TEST(Long)
            TEST(LongDouble)
            TEST(LongLong)
            TEST(Short)
            TEST(UnsignedChar)
            TEST(UnsignedInt)
            TEST(UnsignedLong)
            TEST(UnsignedLongLong)
            TEST(UnsignedShort)

            template <class T>
            static Test::Result test(const T& initial_value, const T& set_value);

        TEST_CASES_END(SetValue)

    TEST_CASES_END(ParameterTemplateBase_test)
}

#endif
