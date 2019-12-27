#if !defined ARGUMENT_VALUE_TEST_HPP
#define ARGUMENT_VALUE_TEST_HPP

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

#include "ArgumentValue.hpp"

TEST_CASES_BEGIN(ArgumentValue_test)

    TEST_CASES_BEGIN(Update)

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
    static Test::Result test(const T&           default_value,
                             const std::string& update_value,
                             const T&           expected_value);

    TEST_CASES_END(Update)

TEST_CASES_END(ArgumentValue_test)

#endif
