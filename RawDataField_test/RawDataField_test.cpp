#include <cstring>
#include <limits>

#include "RawDataField_test.hpp"

#include "RawDataField.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

TEST_PROGRAM_MAIN(RawDataField_test);

//==============================================================================
void RawDataField_test::addTestCases()
{
    ADD_TEST_CASE(Assignment);
    ADD_TEST_CASE(ConstructZeroSize);
    ADD_TEST_CASE(CopyConstructor);
    ADD_TEST_CASE(Equality);
    ADD_TEST_CASE(GetBit_OutOfRange);
    ADD_TEST_CASE(GetBitsAsNumericType_Chunks);
    ADD_TEST_CASE(GetBitsAsNumericType_IncRangesAllSet);
    ADD_TEST_CASE(GetBitsAsNumericType_OutOfRange);
    ADD_TEST_CASE(GetByte);
    ADD_TEST_CASE(GetLengthBytes);
    ADD_TEST_CASE(Inequality);
    ADD_TEST_CASE(ReadRaw);
    ADD_TEST_CASE(SetBit);
    ADD_TEST_CASE(SetBitsAsNumericType_Chunks);
    ADD_TEST_CASE(SetBitsAsNumericType_IncRanges);
    ADD_TEST_CASE(SetByte);
    ADD_TEST_CASE(ShiftDown);
    ADD_TEST_CASE(ShiftUp);
    ADD_TEST_CASE(WriteRaw);
}

//==============================================================================
Test::Result RawDataField_test::ConstructZeroSize::body()
{
    bool exception_caught = false;

    try
    {
        RawDataField rdf(0, misc::BYTES);
    }
    catch (std::invalid_argument& ex)
    {
        exception_caught = true;
    }

    if (exception_caught)
    {
        return Test::PASSED;
    }

    return Test::FAILED;
}

//==============================================================================
Test::Result RawDataField_test::CopyConstructor::body()
{
    RawDataField rdf1(10, misc::BYTES);
    RawDataField rdf2(rdf1);
    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::GetLengthBytes::body()
{
    RawDataField rdf(workspace1, workspace_length, misc::BYTES, false);
    MUST_BE_TRUE(rdf.getLengthBytes() == workspace_length);
    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::WriteRaw::body()
{
    for (unsigned int i = 0; i < workspace_length; i++)
    {
        workspace1[i] = static_cast<unsigned char>(i);
        workspace2[i] = 0;
    }

    RawDataField rdf(workspace1, workspace_length, misc::BYTES, false);
    rdf.DataField::writeRaw(workspace2);

    for (unsigned int i = 0; i < workspace_length; i++)
    {
        MUST_BE_TRUE(workspace2[i] == static_cast<unsigned char>(i));
    }

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::ReadRaw::body()
{
    for (unsigned int i = 0; i < workspace_length; i++)
    {
        workspace1[i] = static_cast<unsigned char>(i);
        workspace2[i] = 0;
    }

    RawDataField rdf(workspace1, workspace_length, misc::BYTES, false);
    rdf.DataField::readRaw(workspace2);

    for (unsigned int i = 0; i < workspace_length; i++)
    {
        MUST_BE_TRUE(workspace1[i] == 0);
    }

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::Equality::body()
{
    RawDataField rdf1(workspace1, workspace_length, misc::BYTES);
    RawDataField rdf2(workspace1, workspace_length, misc::BYTES);
    MUST_BE_TRUE(rdf1 == rdf2);

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::Inequality::body()
{
    RawDataField rdf1(workspace1, workspace_length, misc::BYTES);
    RawDataField rdf2(workspace1, workspace_length, misc::BYTES);
    MUST_BE_FALSE(rdf1 != rdf2);

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::GetByte::body()
{
    RawDataField rdf(workspace1, workspace_length, misc::BYTES, false);

    for (unsigned int i = 0; i < workspace_length; i++)
    {
        MUST_BE_TRUE(workspace1[i] == rdf.getByte(i));
    }

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::SetByte::body()
{
    memset(workspace1, 1, workspace_length);

    RawDataField rdf(workspace1, workspace_length, misc::BYTES, false);

    for (unsigned int i = 0; i < workspace_length; i++)
    {
        rdf.setByte(i, 0);
        MUST_BE_TRUE(workspace1[i] == 0);
    }

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::Assignment::body()
{
    memset(workspace1, 0, workspace_length);
    memset(workspace2, 1, workspace_length);

    RawDataField rdf1(workspace1, workspace_length, misc::BYTES, false);
    RawDataField rdf2(workspace2, workspace_length, misc::BYTES, false);

    rdf1 = rdf2;

    MUST_BE_TRUE(memcmp(workspace1, workspace2, workspace_length) == 0);

    return Test::PASSED;
}

//==============================================================================
// Make sure trying to get out-of-range bits properly throws an exception
//==============================================================================
Test::Result RawDataField_test::GetBit_OutOfRange::body()
{
    RawDataField rdf(1, misc::BYTES);

    bool exception_caught = false;

    try
    {
        rdf.getBit(BITS_PER_BYTE);
    }
    catch (std::out_of_range& ex)
    {
        exception_caught = true;
    }

    MUST_BE_TRUE(exception_caught);

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::SetBit::body()
{
    std::uint8_t  number1 = 0;
    std::uint16_t number2 = 0;
    std::uint32_t number4 = 0;

    RawDataField number_rdf1(&number1, 1, misc::BYTES, false);
    RawDataField number_rdf2(reinterpret_cast<std::uint8_t*>(&number2),
                             sizeof(std::uint16_t),
                             misc::BYTES,
                             false);
    RawDataField number_rdf4(reinterpret_cast<std::uint8_t*>(&number4),
                             sizeof(std::uint32_t),
                             misc::BYTES,
                             false);

    // Test all the bits in a couple different size integers
    MUST_BE_TRUE(setBitAllBits(number_rdf1, number1));
    MUST_BE_TRUE(setBitAllBits(number_rdf2, number2));
    MUST_BE_TRUE(setBitAllBits(number_rdf4, number4));

    // Switch the bit indexing mode and try again
    number_rdf1.setBitIndexingMode(RawDataField::MS_LEAST);
    number_rdf2.setBitIndexingMode(RawDataField::MS_LEAST);
    number_rdf4.setBitIndexingMode(RawDataField::MS_LEAST);
    MUST_BE_TRUE(setBitAllBits(number_rdf1, number1));
    MUST_BE_TRUE(setBitAllBits(number_rdf2, number2));
    MUST_BE_TRUE(setBitAllBits(number_rdf4, number4));

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::ShiftUp::body()
{
    std::uint32_t test_uint32 = 1;

    RawDataField rdf(reinterpret_cast<std::uint8_t*>(&test_uint32),
                     sizeof(std::uint32_t),
                     misc::BYTES,
                     false);

    // Shift all the way up
    for (unsigned int i = 1; i < sizeof(std::uint32_t) * BITS_PER_BYTE; ++i)
    {
        rdf.shiftUp(1); // operation under test
        std::cout << test_uint32 << " ";
        MUST_BE_TRUE(test_uint32 == std::round(std::pow(2, i)));
    }

    // One more shift should get us 0
    rdf.shiftUp(1);
    std::cout << test_uint32 << "\n";
    MUST_BE_TRUE(test_uint32 == 0);

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::ShiftDown::body()
{
    std::uint32_t test_uint32 = std::pow(2, 31);

    RawDataField rdf(reinterpret_cast<std::uint8_t*>(&test_uint32),
                     sizeof(std::uint32_t),
                     misc::BYTES,
                     false);

    // Shift all the way back down
    for (unsigned int i = 30; i != 0; --i)
    {
        rdf.shiftDown(1); // operation under test
        std::cout << test_uint32 << " ";
        MUST_BE_TRUE(test_uint32 == std::round(std::pow(2, i)));
    }

    // One more shift should get us 1
    rdf.shiftDown(1);
    std::cout << test_uint32 << " ";
    MUST_BE_TRUE(test_uint32 == 1);

    // One more should get us 0
    rdf.shiftDown(1);
    std::cout << test_uint32 << "\n";
    MUST_BE_TRUE(test_uint32 == 0);

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::GetBitsAsNumericType_OutOfRange::body()
{
    std::uint32_t test_uint32 = std::pow(2, 31);
    std::uint8_t type1 = 255;

    RawDataField rdf(reinterpret_cast<std::uint8_t*>(&test_uint32),
                     sizeof(std::uint32_t),
                     misc::BYTES,
                     false);

    // Can't get more bits than are in the destination type
    MUST_BE_TRUE(getBitsAsNumericTypeExCaught(rdf, 0, 9,  type1));
    MUST_BE_TRUE(getBitsAsNumericTypeExCaught(rdf, 4, 22, type1));

    // Can't get more bits than are in the bitfield
    MUST_BE_TRUE(getBitsAsNumericTypeExCaught(rdf, 0, 33, type1));

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::GetBitsAsNumericType_IncRangesAllSet::body()
{
    std::uint32_t test_uint32 = std::numeric_limits<std::uint32_t>::max();

    RawDataField rdf(reinterpret_cast<std::uint8_t*>(&test_uint32),
                     sizeof(std::uint32_t),
                     misc::BYTES,
                     false);

    // All bits in rdf are set so the first i bits should equal std::pow(2, i) -
    // 1 when interpreted as an integer
    for (unsigned int i = 0; i <= 32; ++i)
    {
        unsigned int get1 = 0;
        rdf.getBitsAsNumericType(get1, 0, i);
        std::cout << get1 << " ";
        MUST_BE_TRUE(get1 == std::pow(2, i) - 1);
    }
    std::cout << "\n";

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::GetBitsAsNumericType_Chunks::body()
{
    std::uint32_t test_uint32 = std::numeric_limits<std::uint32_t>::max();

    RawDataField rdf(reinterpret_cast<std::uint8_t*>(&test_uint32),
                     sizeof(std::uint32_t),
                     misc::BYTES,
                     false);

    unsigned int get1;

    // Least significant bit of each byte is set
    memset(&test_uint32, 1, 4);

    // Grab the first of the set bits.
    rdf.getBitsAsNumericType(get1, 0, 1);
    MUST_BE_TRUE(get1 == 1); // 2^1

    // Grab all the way up to the second of the set bits.
    rdf.getBitsAsNumericType(get1, 0, 9);
    MUST_BE_TRUE(get1 == 257); // 2^9 - 2^8 + previous answer

    // This is purposefully grabbing more than the three set bits.  Extra
    // grabbed bits should be zero and shouldn't affect the result.
    rdf.getBitsAsNumericType(get1, 0, 18);
    MUST_BE_TRUE(get1 == 65793); // 2^17 - 2^16 + previous answer

    // Purposefully grabbing more than the four set bits.  Extra grabbed bits
    // should be zero and shouldn't affect the result.
    rdf.getBitsAsNumericType(get1, 0, 30);
    MUST_BE_TRUE(get1 == 16843009); // 2^25 - 2^24 + previous answer

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::SetBitsAsNumericType_IncRanges::body()
{
    std::uint32_t test_uint32 = 0;

    RawDataField rdf(reinterpret_cast<std::uint8_t*>(&test_uint32),
                     sizeof(std::uint32_t),
                     misc::BYTES,
                     false);

    std::uint32_t set1 = 0;

    for (unsigned int i = 0; i <= 32; ++i)
    {
        set1 = static_cast<std::uint32_t>(std::pow(2, i) - 1);
        std::cout << set1 << " ";

        rdf.setBitsAsNumericType(set1, 0, i);
        MUST_BE_TRUE(test_uint32 == set1);
    }

    std::cout << "\n";

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test::SetBitsAsNumericType_Chunks::body()
{
    std::uint32_t test_uint32 = 0;

    RawDataField rdf(reinterpret_cast<std::uint8_t*>(&test_uint32),
                     sizeof(std::uint32_t),
                     misc::BYTES,
                     false);

    // Set the first of the bits.
    std::uint32_t set1 = 0b1;
    rdf.setBitsAsNumericType(set1, 0, 1);
    MUST_BE_TRUE(test_uint32 == 1); // 2^1

    // Set all the way up to the second of the set bits.
    set1 = 0b100000001;
    rdf.setBitsAsNumericType(set1, 0, 9);
    MUST_BE_TRUE(test_uint32 == 257); // 2^9 - 2^8 + previous answer

    // This is purposefully setting more than the three set bits.  Extra set
    // bits should be zero and shouldn't affect the result.
    set1 = 0b10000000100000001;
    rdf.setBitsAsNumericType(set1, 0, 18);
    MUST_BE_TRUE(test_uint32 == 65793); // 2^17 - 2^16 + previous answer

    // Purposefully setting more than the four set bits.  Extra set bits should
    // be zero and shouldn't affect the result.
    set1 = 0b1000000010000000100000001;
    rdf.setBitsAsNumericType(set1, 0, 30);
    MUST_BE_TRUE(test_uint32 == 16843009); // 2^25 - 2^24 + previous answer

    return Test::PASSED;
}

//==============================================================================
template<class T> bool setBitAllBits(RawDataField& number_rdf, T& number)
{
    bool all_good = true;

    unsigned int bit_width = sizeof(T) * BITS_PER_BYTE;

    for (unsigned int i = 0; i < bit_width; i++)
    {
        number_rdf.setBit(i, true);

        // Test that the right bit gets set without using any RawDataField
        // functionality
        if (number_rdf.getBitIndexingMode() == RawDataField::LS_LEAST)
        {
            all_good = number == std::round(std::pow(2, i));
        }
        else if (number_rdf.getBitIndexingMode() == RawDataField::MS_LEAST)
        {
            std::ldiv_t div_result = std::ldiv(i, BITS_PER_BYTE);

            all_good = number ==
                static_cast<T>(
                    std::pow(2, (BITS_PER_BYTE - div_result.rem) - 1)) <<
                (div_result.quot * BITS_PER_BYTE);
        }
        else
        {
            all_good = false;
        }

        std::cout << number << " ";

        if (!all_good) break;

        // Test that the right bit gets set by using getBit()
        all_good = number_rdf.getBit(i);
        if (!all_good) break;

        number_rdf.setBit(i, false);
        all_good = number == 0;
        if (!all_good) break;
    }

    std::cout << "\n";

    return all_good;
}

//==============================================================================
template <class T> bool getBitsAsNumericTypeExCaught(RawDataField& bitfield,
                                                     unsigned int  start_bit,
                                                     unsigned int  count,
                                                     T&            dest_type)
{
    bool exception_caught = false;

    try
    {
        bitfield.getBitsAsNumericType(start_bit, count, dest_type);
    }
    catch (std::out_of_range& ex)
    {
        exception_caught = true;
    }

    return exception_caught;
}
