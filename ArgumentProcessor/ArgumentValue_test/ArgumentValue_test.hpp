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

    TEST_CASES_BEGIN(OperatorLessThan)

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
        static Test::Result test(const T& value1, const T& value2);

    TEST_CASES_END(OperatorLessThan)

    TEST_CASES_BEGIN(OperatorGreaterThan)

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
        static Test::Result test(const T& value1, const T& value2);

    TEST_CASES_END(OperatorGreaterThan)

    TEST_CASES_BEGIN(OperatorLessThanOrEqualTo)

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
        static Test::Result test(const T& value1, const T& value2);

    TEST_CASES_END(OperatorLessThanOrEqualTo)

    TEST_CASES_BEGIN(OperatorGreaterThanOrEqualTo)

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
        static Test::Result test(const T& value1, const T& value2);

    TEST_CASES_END(OperatorGreaterThanOrEqualTo)

    TEST_CASES_BEGIN(OperatorEquality)

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
        static Test::Result test(const T& value1, const T& value2);

    TEST_CASES_END(OperatorEquality)

    TEST_CASES_BEGIN(OperatorNotEqual)

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
        static Test::Result test(const T& value1, const T& value2);

        TEST_CASES_END(OperatorNotEqual)

TEST_CASES_END(ArgumentValue_test)

#endif
