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
