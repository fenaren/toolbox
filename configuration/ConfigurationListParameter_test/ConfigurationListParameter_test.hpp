#if !defined CONFIGURATION_LIST_PARAMETER_TEST_HPP
#define CONFIGURATION_LIST_PARAMETER_TEST_HPP

#include <list>

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

#include "ConfigurationListParameter.hpp"

namespace Configuration
{

    TEST_CASES_BEGIN(ListParameter_test)

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
            static Test::Result test(const std::list<T>& default_value,
                                     const std::string&  update_value,
                                     const std::list<T>& expected_value);

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
            static Test::Result test(const std::list<T>& value1,
                                     const std::list<T>& value2);

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
            static Test::Result test(const std::list<T>& value1,
                                     const std::list<T>& value2);

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
            static Test::Result test(const std::list<T>& value1,
                                     const std::list<T>& value2);

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
            static Test::Result test(const std::list<T>& value1,
                                     const std::list<T>& value2);

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
            static Test::Result test(const std::list<T>& value1,
                                     const std::list<T>& value2);

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
            static Test::Result test(const std::list<T>& value1,
                                     const std::list<T>& value2);

        TEST_CASES_END(OperatorNotEqual)

    TEST_CASES_END(ListParameter_test)

}

#endif
