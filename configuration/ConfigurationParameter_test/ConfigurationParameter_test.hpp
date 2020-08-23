#if !defined CONFIGURATION_PARAMETER_TEST_HPP
#define CONFIGURATION_PARAMETER_TEST_HPP

#include <list>
#include <string>

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

namespace Configuration
{
    TEST_CASES_BEGIN(Parameter_test)

        TEST(Generic)

        TEST_CASES_BEGIN(List)

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

                template <class T> static Test::Result test(const std::string&  initial_value,
                                                            const std::list<T>& should_equal);

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

                template <class T> static Test::Result test(const std::list<T>& initial_value,
                                                            const std::string&  should_equal);

            TEST_CASES_END(ToString)

        TEST_CASES_END(List)

    TEST_CASES_END(Parameter_test)
}

#endif
