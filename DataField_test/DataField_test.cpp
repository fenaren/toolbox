#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <limits>

#include "DataField_test.hpp"

#include "DataField.hpp"
#include "SimpleDataField.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(DataField_test)

//==============================================================================
void DataField_test::addTestCases()
{
    ADD_TEST_CASE(WriteRaw);
    ADD_TEST_CASE(ReadRaw);
    ADD_TEST_CASE(ReadRawConst);
    ADD_TEST_CASE(WriteAndReadRaw);
    ADD_TEST_CASE(NormalizeMemoryLocation);
    ADD_TEST_CASE(NormalizeMemoryLocationConst);
}

//==============================================================================
void DataField_test::WriteRaw::addTestCases()
{
    ADD_TEST_CASE(BitOffset);
}

//==============================================================================
void DataField_test::ReadRaw::addTestCases()
{
    ADD_TEST_CASE(BitOffset);
    ADD_TEST_CASE(NoBitOffset);
}

//==============================================================================
void DataField_test::ReadRawConst::addTestCases()
{
    ADD_TEST_CASE(BitOffset);
    ADD_TEST_CASE(NoBitOffset);
}

//==============================================================================
void DataField_test::WriteAndReadRaw::addTestCases()
{
    ADD_TEST_CASE(UnsignedInt1Byte);
    ADD_TEST_CASE(UnsignedInt2Byte);
    ADD_TEST_CASE(UnsignedInt4Byte);
}

//==============================================================================
void DataField_test::NormalizeMemoryLocation::addTestCases()
{
    ADD_TEST_CASE(Buffer0Bits0);
    ADD_TEST_CASE(Buffer0Bits8);
    ADD_TEST_CASE(Buffer1Bits16);
    ADD_TEST_CASE(Buffer2Bits404);
}

//==============================================================================
void DataField_test::NormalizeMemoryLocationConst::addTestCases()
{
    ADD_TEST_CASE(Buffer0Bits0);
    ADD_TEST_CASE(Buffer0Bits8);
    ADD_TEST_CASE(Buffer1Bits16);
    ADD_TEST_CASE(Buffer2Bits404);
}

//==============================================================================
Test::Result DataField_test::WriteRaw::BitOffset::body()
{
    return Test::SKIPPED;
}

//==============================================================================
Test::Result DataField_test::ReadRaw::BitOffset::body()
{
    return Test::SKIPPED;
}

//==============================================================================
Test::Result DataField_test::ReadRaw::NoBitOffset::body()
{
    return Test::SKIPPED;
}

//==============================================================================
Test::Result DataField_test::ReadRawConst::BitOffset::body()
{
    return Test::SKIPPED;
}

//==============================================================================
Test::Result DataField_test::ReadRawConst::NoBitOffset::body()
{
    return Test::SKIPPED;
}

//==============================================================================
Test::Result DataField_test::WriteAndReadRaw::UnsignedInt1Byte::body()
{
    MUST_BE_TRUE(writeAndReadRawTest<std::uint8_t>());
    return Test::PASSED;
}

//==============================================================================
Test::Result DataField_test::WriteAndReadRaw::UnsignedInt2Byte::body()
{
    MUST_BE_TRUE(writeAndReadRawTest<std::uint16_t>());
    return Test::PASSED;
}

//==============================================================================
Test::Result DataField_test::WriteAndReadRaw::UnsignedInt4Byte::body()
{
    MUST_BE_TRUE(writeAndReadRawTest<std::uint32_t>());
    return Test::PASSED;
}

//==============================================================================
template <class T> bool writeAndReadRawTest()
{
    // With this test we're going to write a simple integer data field set to 0
    // into a buffer of 1s that is double the integer's size at successively
    // greater offsets.  As we go along the first half of the buffer will lose
    // 0s and the second half will gain 0s.  We can predict exactly what both
    // halves should be equal to as integers, so we check this with each offset
    // write.

    // Will go false if the test fails
    bool passed = true;

    const unsigned int workarea_size = sizeof(T) * 2;
    T workarea[2];

    for (unsigned int i = 0; i <= sizeof(T) * BITS_PER_BYTE; ++i)
    {
        // Set the entire work area to all ones
        memset(workarea, 0xff, workarea_size);

        // We'll shift this 0 across the whole work area one bit at a time,
        // checking the value of both halves against math
        SimpleDataField<T> test_sdf(0);

        T something = std::pow(2, i) - 1;

        // Work area halves should equal these two values after the write
        T correct_firsthalf = something;
        T correct_secondhalf = std::numeric_limits<T>::max() - something;

        // Actually do the write
        test_sdf.DataField::writeRaw(
            reinterpret_cast<std::uint8_t*>(workarea), i);

        // Now check both halves
        std::cout << "Offset " << i << " " << workarea[0] << " ";
        if (workarea[0] != correct_firsthalf)
        {
            std::cout << "(WRONG should be " << correct_firsthalf << ") ";
            passed = false;
        }

        std::cout << workarea[1] << " ";
        if (workarea[1] != correct_secondhalf)
        {
            std::cout << "(WRONG should be " << correct_secondhalf << ") ";
            passed = false;
        }

        std::cout << "\n";

        if (!passed)
        {
            break;
        }

        // So the write seems to have worked, if we've reached this point.  Try
        // to read back the field we just wrote and make sure it's zero.  Also
        // make sure the readRaw operation doesn't change the contents of the
        // workarea

        T workarea_copy[2];
        memcpy(workarea_copy, workarea, sizeof(T) * 2);

        test_sdf.DataField::readRaw(
            reinterpret_cast<std::uint8_t*>(workarea), i);

        if (memcmp(workarea, workarea_copy, sizeof(T) * 2) != 0)
        {
            std::cout << "readRaw modified buffer contents, should not have\n";
            passed = false;
            break;
        }

        if (test_sdf != 0)
        {
            std::cout << "Readback failed, should have read 0\n";
            passed = false;
            break;
        }
    }

    return passed;
}

//==============================================================================
Test::Result DataField_test::NormalizeMemoryLocation::Buffer0Bits0::body()
{
    return NML_BufferBits(0, 0, 0, 0);
}

//==============================================================================
Test::Result DataField_test::NormalizeMemoryLocation::Buffer0Bits8::body()
{
    return NML_BufferBits(0, 8, reinterpret_cast<std::uint8_t*>(1), 0);
}

//==============================================================================
Test::Result DataField_test::NormalizeMemoryLocation::Buffer1Bits16::body()
{
    return NML_BufferBits(reinterpret_cast<std::uint8_t*>(1),
                          16,
                          reinterpret_cast<std::uint8_t*>(3),
                          0);
}

//==============================================================================
Test::Result DataField_test::NormalizeMemoryLocation::Buffer2Bits404::body()
{
    return NML_BufferBits(reinterpret_cast<std::uint8_t*>(2),
                          404,
                          reinterpret_cast<std::uint8_t*>(52),
                          4);
}

//==============================================================================
Test::Result DataField_test::NormalizeMemoryLocationConst::Buffer0Bits0::body()
{
    return NML_BufferBitsConst(0, 0, 0, 0);
}

//==============================================================================
Test::Result DataField_test::NormalizeMemoryLocationConst::Buffer0Bits8::body()
{
    return NML_BufferBitsConst(0, 8, reinterpret_cast<std::uint8_t*>(1), 0);
}

//==============================================================================
Test::Result DataField_test::NormalizeMemoryLocationConst::Buffer1Bits16::body()
{
    return NML_BufferBitsConst(reinterpret_cast<std::uint8_t*>(1),
                               16,
                               reinterpret_cast<std::uint8_t*>(3),
                               0);
}

//==============================================================================
Test::Result DataField_test::NormalizeMemoryLocationConst::Buffer2Bits404::body()
{
    return NML_BufferBitsConst(reinterpret_cast<std::uint8_t*>(2),
                               404,
                               reinterpret_cast<std::uint8_t*>(52),
                               4);
}

//==============================================================================
Test::Result DataField_test::NML_BufferBits(std::uint8_t* buffer_before,
                                            unsigned long bits_before,
                                            std::uint8_t* buffer_after,
                                            unsigned long bits_after)
{
    // Non-const object to run this function in association with
    SimpleDataField<int> sdf;

    std::uint8_t* buffer = buffer_before;
    unsigned long bits   = bits_before;

    sdf.normalizeMemoryLocation(buffer, bits);
    MUST_BE_TRUE(buffer == buffer_after && bits == bits_after);

    return Test::PASSED;
}

//==============================================================================
Test::Result DataField_test::NML_BufferBitsConst(std::uint8_t* buffer_before,
                                                 unsigned long bits_before,
                                                 std::uint8_t* buffer_after,
                                                 unsigned long bits_after)
{
    // Non-const object to run this function in association with
    const SimpleDataField<int> sdf;

    std::uint8_t* buffer = buffer_before;
    unsigned long bits   = bits_before;

    sdf.normalizeMemoryLocation(buffer, bits);
    MUST_BE_TRUE(buffer == buffer_after && bits == bits_after);

    return Test::PASSED;
}
