#if !defined RAW_DATA_FIELD_TEST
#define RAW_DATA_FIELD_TEST

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

class RawDataField;

TEST_CASES_BEGIN(RawDataField_test)

    TEST(Assignment)
    TEST(ConstructZeroSize)
    TEST(CopyConstructor)
    TEST(Equality)
    TEST(GetBit_OutOfRange)
    TEST(GetBitsAsNumericType_Chunks)
    TEST(GetBitsAsNumericType_IncRangesAllSet)
    TEST(GetBitsAsNumericType_OutOfRange)
    TEST(GetByte)
    TEST(GetLengthBytes)
    TEST(Inequality)
    TEST(ReadRaw)
    TEST(SetBit)
    TEST(SetBitsAsNumericType_Chunks)
    TEST(SetBitsAsNumericType_IncRanges)
    TEST(SetByte)
    TEST(ShiftDown)
    TEST(ShiftUp)
    TEST(WriteRaw)

TEST_CASES_END(RawDataField_test)

// Some memory for all test cases to use
const unsigned int workspace_length = 20;
unsigned char workspace1[workspace_length];
unsigned char workspace2[workspace_length];

// Free utility functions
template <class T> bool setBitAllBits(RawDataField& number_rdf, T& number);
template <class T> bool getBitsAsNumericTypeExCaught(RawDataField& bitfield,
                                                     unsigned int  start_bit,
                                                     unsigned int  count,
                                                     T&            dest_type);

#endif
