#if !defined DATA_FIELD_TEST
#define DATA_FIELD_TEST

#include <cstdint>

#include "Test.hpp"
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

    // Tests the normalizeMemoryLocation member function
    TEST_CASES_BEGIN(NormalizeMemoryLocation)

        TEST(Buffer0Bits0)
        TEST(Buffer0Bits8)
        TEST(Buffer1Bits16)
        TEST(Buffer2Bits404)

    TEST_CASES_END(NormalizeMemoryLocation)

    TEST_CASES_BEGIN(NormalizeMemoryLocationConst)

        TEST(Buffer0Bits0)
        TEST(Buffer0Bits8)
        TEST(Buffer1Bits16)
        TEST(Buffer2Bits404)

    TEST_CASES_END(NormalizeMemoryLocationConst)

    static Test::Result NML_BufferBits(std::uint8_t* buffer_before,
                                       unsigned long bits_before,
                                       std::uint8_t* buffer_after,
                                       unsigned long bits_after);

    static Test::Result NML_BufferBitsConst(std::uint8_t* buffer_before,
                                            unsigned long bits_before,
                                            std::uint8_t* buffer_after,
                                            unsigned long bits_after);

TEST_CASES_END(DataField_test)

template <class T> bool writeAndReadRawTest();

#endif
