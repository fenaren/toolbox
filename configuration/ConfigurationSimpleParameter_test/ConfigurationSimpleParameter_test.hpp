#if !defined CONFIGURATION_SIMPLE_PARAMETER_TEST_HPP
#define CONFIGURATION_SIMPLE_PARAMETER_TEST_HPP

#include <string>

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

namespace Configuration
{
    TEST_CASES_BEGIN(SimpleParameter_test)

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

        TEST_CASES_BEGIN(OperatorStreamInsertion)

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

        TEST_CASES_END(OperatorStreamInsertion)

        TEST_CASES_BEGIN(OperatorStreamExtraction)

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

        TEST_CASES_END(OperatorStreamExtraction)

    TEST_CASES_END(SimpleParameter_test)
}

#endif
