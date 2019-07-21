#if !defined RAW_DATA_FIELD_TEST
#define RAW_DATA_FIELD_TEST

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

class RawDataField;

TEST_CASES_BEGIN(RawDataField_test)

    TEST(Constructor)
    TEST(CopyConstructor)
    TEST(GetBit)

    TEST_CASES_BEGIN(GetBitsAsNumericType)

        TEST(Chunks)
        TEST(IncRangesAllSet)
        TEST(OutOfRange)

    TEST_CASES_END(GetBitsAsNumericType)

    TEST(GetByte)
    TEST(GetLengthBytes)

    TEST_CASES_BEGIN(Operators)

        TEST(EqualTo)
        TEST(NotEqualTo)
        TEST(SimpleAssignment)

    TEST_CASES_END(Operators)

    TEST(ReadRaw)
    TEST(SetBit)

    TEST_CASES_BEGIN(SetBitsAsNumericType)

        TEST(Chunks)
        TEST(IncRanges)

    TEST_CASES_END(SetBitsAsNumericType)

    TEST(SetByte)
    TEST(ShiftDown)
    TEST(ShiftUp)
    TEST(WriteRaw)

    template <class T> static bool setBitAllBits(RawDataField& number_rdf,
                                                 T&            number);

    template <class T> static bool getBitsAsNumericTypeExCaught(
        RawDataField& bitfield,
        unsigned int  start_bit,
        unsigned int  count,
        T&            dest_type);

    static const unsigned int workspace_length = 20;

TEST_CASES_END(RawDataField_test)

#endif
