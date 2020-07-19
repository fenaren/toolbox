#if !defined CONFIGURATION_SIMPLE_PARAMETER_TEST_HPP
#define CONFIGURATION_SIMPLE_PARAMETER_TEST_HPP

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

#include "ConfigurationSimpleParameter.hpp"

namespace Configuration
{
    TEST_CASES_BEGIN(SimpleParameter_test)

        TEST_CASES_BEGIN(SetValue)

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

        TEST_CASES_BEGIN(OperatorLessThan)

            TEST(StringConstCharP)
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

            template <class T> static Test::Result test(const T& value1, const T& value2);

        TEST_CASES_END(OperatorLessThan)

        TEST_CASES_BEGIN(OperatorGreaterThan)

            TEST(StringConstCharP)
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

            template <class T> static Test::Result test(const T& value1, const T& value2);

        TEST_CASES_END(OperatorGreaterThan)

        TEST_CASES_BEGIN(OperatorLessThanOrEqualTo)

            TEST(StringConstCharP)
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

            template <class T> static Test::Result test(const T& value1, const T& value2);

        TEST_CASES_END(OperatorLessThanOrEqualTo)

        TEST_CASES_BEGIN(OperatorGreaterThanOrEqualTo)

            TEST(StringConstCharP)
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

            template <class T> static Test::Result test(const T& value1, const T& value2);

        TEST_CASES_END(OperatorGreaterThanOrEqualTo)

        TEST_CASES_BEGIN(OperatorEquality)

            TEST(StringConstCharP)
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

            template <class T> static Test::Result test(const T& value1, const T& value2);

        TEST_CASES_END(OperatorEquality)

        TEST_CASES_BEGIN(OperatorNotEqual)

            TEST(StringConstCharP)
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

            template <class T> static Test::Result test(const T& value1, const T& value2);

        TEST_CASES_END(OperatorNotEqual)

        TEST_CASES_BEGIN(FromString)

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

            template <class T> static Test::Result test(const std::string& initial_value,
                                                        const T&           should_equal);

        TEST_CASES_END(FromString)

        TEST_CASES_BEGIN(ToString)

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

            template <class T> static Test::Result test(const T&           initial_value,
                                                        const std::string& should_equal);

        TEST_CASES_END(ToString)

    TEST_CASES_END(SimpleParameter_test)
}

#endif
