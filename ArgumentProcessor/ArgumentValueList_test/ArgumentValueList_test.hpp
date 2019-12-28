#if !defined ARGUMENT_VALUE_LIST_TEST_HPP
#define ARGUMENT_VALUE_LIST_TEST_HPP

#include <list>

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

#include "ArgumentValueList.hpp"

TEST_CASES_BEGIN(ArgumentValueList_test)

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

    // Relational operators
    TEST(OperatorEquality)
    TEST(OperatorNotEqual)

TEST_CASES_END(ArgumentValueList_test)

#endif
