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
    ADD_TEST_CASE(WriteRawConst);
    ADD_TEST_CASE(ReadRaw);
    ADD_TEST_CASE(ReadRawConstBuffer);
    ADD_TEST_CASE(NormalizeMemoryLocation);
    ADD_TEST_CASE(NormalizeMemoryLocationConst);
}

//==============================================================================
void DataField_test::WriteRawConst::addTestCases()
{
    ADD_TEST_CASE(Byte1);
    ADD_TEST_CASE(Byte2);
    ADD_TEST_CASE(Byte4);
}

//==============================================================================
void DataField_test::ReadRaw::addTestCases()
{
    ADD_TEST_CASE(Byte1);
    ADD_TEST_CASE(Byte2);
    ADD_TEST_CASE(Byte4);
}

//==============================================================================
void DataField_test::ReadRawConstBuffer::addTestCases()
{
    ADD_TEST_CASE(Byte1);
    ADD_TEST_CASE(Byte2);
    ADD_TEST_CASE(Byte4);
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
Test::Result DataField_test::WriteRawConst::Byte1::body()
{
    return writeRawSlidingWindow<std::uint8_t>();
}

//==============================================================================
Test::Result DataField_test::WriteRawConst::Byte2::body()
{
    return writeRawSlidingWindow<std::uint16_t>();
}

//==============================================================================
Test::Result DataField_test::WriteRawConst::Byte4::body()
{
    return writeRawSlidingWindow<std::uint32_t>();
}

//==============================================================================
Test::Result DataField_test::ReadRaw::Byte1::body()
{
    return readRawSlidingWindow<std::uint8_t>();
}

//==============================================================================
Test::Result DataField_test::ReadRaw::Byte2::body()
{
    return readRawSlidingWindow<std::uint16_t>();
}

//==============================================================================
Test::Result DataField_test::ReadRaw::Byte4::body()
{
    return readRawSlidingWindow<std::uint32_t>();
}

//==============================================================================
Test::Result DataField_test::ReadRawConstBuffer::Byte1::body()
{
    return readRawSlidingWindow<std::uint8_t>();
}

//==============================================================================
Test::Result DataField_test::ReadRawConstBuffer::Byte2::body()
{
    return readRawSlidingWindow<std::uint16_t>();
}

//==============================================================================
Test::Result DataField_test::ReadRawConstBuffer::Byte4::body()
{
    return readRawSlidingWindow<std::uint32_t>();
}

//==============================================================================
template <class T>
Test::Result DataField_test::WriteRawConst::writeRawSlidingWindow()
{
    // With this test we're going to write a simple integer data field set to 0
    // into a buffer of 1s that is double the integer's size at successively
    // greater offsets.  As we go along the first half of the buffer will lose
    // 0s and the second half will gain 0s.  We can predict exactly what both
    // halves should be equal to as integers, so we check this with each offset
    // write.

    const unsigned int workarea_size = sizeof(T) * 2;
    T workarea[2];

    for (unsigned int i = 0; i <= sizeof(T) * BITS_PER_BYTE; ++i)
    {
        // Set the entire work area to all ones
        memset(workarea, 0xff, workarea_size);

        // We'll shift this 0 across the whole work area one bit at a time,
        // checking the value of both halves against math
        SimpleDataField<T> test_sdf(0);

        // Work area halves should equal these two values after the write
        T correct_firsthalf = static_cast<T>(std::pow(2, i) - 1);
        T correct_secondhalf =
            std::numeric_limits<T>::max() - correct_firsthalf;

        // Actually do the write
        test_sdf.DataField::writeRaw(
            reinterpret_cast<std::uint8_t*>(workarea), i);

        // Now check both halves
        std::cout << "Offset " << i << " " << workarea[0] << " ";
        MUST_BE_TRUE(workarea[0] == correct_firsthalf)

        std::cout << workarea[1] << " ";
        MUST_BE_TRUE(workarea[1] == correct_secondhalf)

        std::cout << "\n";
    }

    return Test::PASSED;
}

//==============================================================================
template <class T>
Test::Result DataField_test::ReadRaw::readRawSlidingWindow()
{
    // Treat the workarea as a single big-endian integer.  We want to start by
    // setting the low half to zero and then shift the whole half section across
    // to the other half, one bit at a time.  As we do this we test readRaw by
    // telling it to read the section that should be zero and seeing if it
    // actually does come up with zero.

    T workarea[2];

    for (unsigned int i = 0; i <= sizeof(T) * BITS_PER_BYTE; ++i)
    {
        workarea[0] = static_cast<T>(std::pow(2, i) - 1);
        workarea[1] = std::numeric_limits<T>::max() - workarea[0];

        SimpleDataField<T> test_sdf;
        test_sdf.DataField::readRaw(
            reinterpret_cast<std::uint8_t*>(workarea), misc::ENDIAN_BIG, i);

        MUST_BE_TRUE(test_sdf == 0);
    }

    return Test::PASSED;
}

//==============================================================================
template <class T>
Test::Result DataField_test::ReadRawConstBuffer::readRawSlidingWindow()
{
    // Treat the workarea as a single big-endian integer.  We want to start by
    // setting the low half to zero and then shift the whole half section across
    // to the other half, one bit at a time.  As we do this we test readRaw by
    // telling it to read the section that should be zero and seeing if it
    // actually does come up with zero.

    T workarea[2];

    for (unsigned int i = 0; i <= sizeof(T) * BITS_PER_BYTE; ++i)
    {
        workarea[0] = static_cast<T>(std::pow(2, i) - 1);
        workarea[1] = std::numeric_limits<T>::max() - workarea[0];

        SimpleDataField<T> test_sdf;

        try
        {
            // Reading from a const buffer with a bit offset is unimplemented
            // and is supposed to generate an exception
            test_sdf.DataField::readRaw(
                reinterpret_cast<const std::uint8_t*>(workarea),
                misc::ENDIAN_BIG,
                i);
        }
        catch (std::runtime_error&)
        {
            // We're supposed to be here if we just asked readRaw to do the
            // thing that we know will generate an exception
            MUST_BE_TRUE(i % BITS_PER_BYTE != 0);
        }

        MUST_BE_TRUE(test_sdf == 0);
    }

    return Test::PASSED;
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
Test::Result
DataField_test::NormalizeMemoryLocationConst::Buffer2Bits404::body()
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
