#if !defined SIMPLE_DATA_FIELD_TEST
#define SIMPLE_DATA_FIELD_TEST

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(SimpleDataField_test);

    TEST_CASES_BEGIN(GetLengthBytes)

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
        TEST(CaseUnsignedShort)

        template <class T> static Test::Result test();

    TEST_CASES_END(GetLengthBytes)

    TEST_CASES_BEGIN(GetValue)

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

        template <class T> static Test::Result test();

    TEST_CASES_END(GetValue)

    TEST_CASES_BEGIN(ReadRaw)

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

        template <class T> static Test::Result test();

    TEST_CASES_END(ReadRaw)

    TEST_CASES_BEGIN(SimpleAssignment)

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

        template <class T> static Test::Result test();

    TEST_CASES_END(SimpleAssignment)

    TEST_CASES_BEGIN(WriteRaw)

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

        template <class T> static Test::Result test();

    TEST_CASES_END(WriteRaw)

TEST_CASES_END(SimpleDataField_test);

#endif
