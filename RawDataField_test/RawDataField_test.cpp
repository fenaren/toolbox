#include <cstring>

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

#include "RawDataField.hpp"

TEST_CASES_PROGRAM(RawDataField_test)
TEST(RawDataField_test_construct_zero_size)
TEST(RawDataField_test_copy_constructor)
TEST(RawDataField_test_getLengthBytes)
TEST(RawDataField_test_writeRaw)
TEST(RawDataField_test_readRaw)
TEST(RawDataField_test_equality)
TEST(RawDataField_test_inequality)
TEST(RawDataField_test_getByte)
TEST(RawDataField_test_setByte)
TEST(RawDataField_test_assignment)
TEST(RawDataField_test_getBit_outOfRange)
TEST(RawDataField_test_setBit)
TEST(RawDataField_test_shiftUp)
TEST(RawDataField_test_shiftDown)
TEST(RawDataField_test_getBitsAsNumericType_outOfRange)
TEST(RawDataField_test_getBitsAsNumericType_incRangesAllSet)
TEST(RawDataField_test_getBitsAsNumericType_chunks)
TEST(RawDataField_test_setBitsAsNumericType_incRanges)
TEST(RawDataField_test_setBitsAsNumericType_chunks)

// Some memory for all test cases to use
const unsigned int workspace_length = 20;
unsigned char workspace1[workspace_length];
unsigned char workspace2[workspace_length];

// Free utility functions
template<class T>  bool setBitAllBits(RawDataField& number_rdf, T& number);
template <class T> bool getBitsAsNumericTypeExCaught(RawDataField& bitfield,
                                                     unsigned int  start_bit,
                                                     unsigned int  count,
                                                     T&            dest_type);

//==============================================================================
void RawDataField_test::addTestCases()
{
    addTestCase(new RawDataField_test_construct_zero_size());
    addTestCase(new RawDataField_test_copy_constructor());
    addTestCase(new RawDataField_test_getLengthBytes());

    // readRaw test must be executed immediately after the writeRaw test
    addTestCase(new RawDataField_test_writeRaw());
    addTestCase(new RawDataField_test_readRaw());

    addTestCase(new RawDataField_test_equality());
    addTestCase(new RawDataField_test_inequality());
    addTestCase(new RawDataField_test_getByte());
    addTestCase(new RawDataField_test_setByte());
    addTestCase(new RawDataField_test_assignment());
    addTestCase(new RawDataField_test_getBit_outOfRange());
    addTestCase(new RawDataField_test_setBit());
    addTestCase(new RawDataField_test_shiftUp());
    addTestCase(new RawDataField_test_shiftDown());
    addTestCase(new RawDataField_test_getBitsAsNumericType_outOfRange());
    addTestCase(new RawDataField_test_getBitsAsNumericType_incRangesAllSet());
    addTestCase(new RawDataField_test_getBitsAsNumericType_chunks());
    addTestCase(new RawDataField_test_setBitsAsNumericType_incRanges());
    addTestCase(new RawDataField_test_setBitsAsNumericType_chunks());
}

//==============================================================================
Test::Result RawDataField_test_construct_zero_size::body()
{
    // Makes no sense to create an bit field of 0 bytes but we should test
    // it here
    RawDataField rdf(0, misc::BYTES); // Dynamic allocation
    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test_copy_constructor::body()
{
    RawDataField rdf1(10, misc::BYTES);
    RawDataField rdf2(rdf1);
    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test_getLengthBytes::body()
{
    RawDataField rdf(workspace1, workspace_length, misc::BYTES, false);
    MUST_BE_TRUE(rdf.getLengthBytes() == workspace_length);
    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test_writeRaw::body()
{
    for (unsigned int i = 0; i < workspace_length; i++)
    {
        workspace1[i] = static_cast<unsigned char>(i);
    }

    RawDataField rdf(workspace1, workspace_length, misc::BYTES, false);

    // Tests writeRaw
    rdf.DataField::writeRaw(workspace2);
    MUST_BE_TRUE(memcmp(workspace1, workspace2, workspace_length) == 0);

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test_readRaw::body()
{
    RawDataField rdf(workspace_length, misc::BYTES);
    rdf.DataField::readRaw(workspace2);

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test_equality::body()
{
    RawDataField rdf1(workspace1, workspace_length, misc::BYTES);
    RawDataField rdf2(workspace1, workspace_length, misc::BYTES);
    MUST_BE_TRUE(rdf1 == rdf2);
    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test_inequality::body()
{
    RawDataField rdf1(workspace1, workspace_length, misc::BYTES);
    RawDataField rdf2(workspace1, workspace_length, misc::BYTES);
    MUST_BE_FALSE(rdf1 != rdf2);
    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test_getByte::body()
{
    RawDataField rdf(workspace1, workspace_length, misc::BYTES, false);

    for (unsigned int i = 0; i < workspace_length; i++)
    {
        MUST_BE_TRUE(workspace1[i] == rdf.getByte(i));
    }

    return Test::PASSED;
}

//==============================================================================
Test::Result RawDataField_test_setByte::body()
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
Test::Result RawDataField_test_assignment::body()
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
Test::Result RawDataField_test_getBit_outOfRange::body()
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
Test::Result RawDataField_test_setBit::body()
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
Test::Result RawDataField_test_shiftUp::body()
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
Test::Result RawDataField_test_shiftDown::body()
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
Test::Result RawDataField_test_getBitsAsNumericType_outOfRange::body()
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
Test::Result RawDataField_test_getBitsAsNumericType_incRangesAllSet::body()
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
Test::Result RawDataField_test_getBitsAsNumericType_chunks::body()
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
Test::Result RawDataField_test_setBitsAsNumericType_incRanges::body()
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
Test::Result RawDataField_test_setBitsAsNumericType_chunks::body()
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
