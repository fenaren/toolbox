#if !defined DATA_FIELD_TEST
#define DATA_FIELD_TEST

#include "TestMacros.hpp"

TEST_CASES_BEGIN(DataField_test)

    // Tests the writeRaw member function
    TEST_CASES_BEGIN(WriteRaw)

        TEST(BitOffset)
        // The NoBitOffset case directly calls another user-defined function

    TEST_CASES_END(WriteRaw)

    // Tests the readRaw member function
    TEST_CASES_BEGIN(ReadRaw)

        TEST(BitOffset)
        TEST(NoBitOffset)

    TEST_CASES_END(ReadRaw)

    // Tests the readRaw const member function
    TEST_CASES_BEGIN(ReadRawConst)

        TEST(BitOffset)
        TEST(NoBitOffset)

    TEST_CASES_END(ReadRawConst)

    // A slightly more complicated test involving both readRaw and writeRaw
    // member functions
    TEST_CASES_BEGIN(WriteAndReadRaw)

        TEST(UnsignedInt1Byte)
        TEST(UnsignedInt2Byte)
        TEST(UnsignedInt4Byte)

    TEST_CASES_END(WriteAndReadRaw)

TEST_CASES_END(DataField_test)

template <class T> bool writeAndReadRawTest();

#endif
