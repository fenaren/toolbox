#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "RawDataField.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

TEST_HEADER(RawDataField_test_case3);
TEST_CONSTRUCTOR_DESTRUCTOR(RawDataField_test_case3);

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

//==============================================================================
Test::Result RawDataField_test_case3::body()
{
    std::uint32_t test_uint32 = 1;
    RawDataField bitfield1(reinterpret_cast<std::uint8_t*>(&test_uint32),
                           sizeof(std::uint32_t),
                           misc::BYTES,
                           false);

    // Shift all the way up
    for (unsigned int i = 1;
         i < sizeof(std::uint32_t) * BITS_PER_BYTE;
         ++i)
    {
        bitfield1.shiftUp(1); // operation under test
        std::cout << test_uint32 << " ";
        MUST_BE_TRUE(test_uint32 == std::round(std::pow(2, i)));
    }

    // One more shift should get us 0
    bitfield1.shiftUp(1);
    std::cout << test_uint32 << "\n";
    MUST_BE_TRUE(test_uint32 == 0);

    // Put the bit back
    bitfield1.setBit(31, true);

    // Shift all the way back down
    for (unsigned int i = 30; i != 0; --i)
    {
        bitfield1.shiftDown(1); // operation under test
        std::cout << test_uint32 << " ";
        MUST_BE_TRUE(test_uint32 == std::round(std::pow(2, i)));
    }

    // One more shift should get us 1
    bitfield1.shiftDown(1);
    std::cout << test_uint32 << " ";
    MUST_BE_TRUE(test_uint32 == 1);

    // One more should get us 0
    bitfield1.shiftDown(1);
    std::cout << test_uint32 << "\n";
    MUST_BE_TRUE(test_uint32 == 0);

    std::uint8_t type1 = 255;

    // Can't get more bits than are in the destination type
    MUST_BE_TRUE(getBitsAsNumericTypeExCaught(bitfield1, 0, 9,  type1));
    MUST_BE_TRUE(getBitsAsNumericTypeExCaught(bitfield1, 4, 22, type1));

    // Can't get more bits than are in the bitfield
    MUST_BE_TRUE(getBitsAsNumericTypeExCaught(bitfield1, 0, 33, type1));

    // GETBITSASNUMERICTYPE TESTED BELOW

    // bitfield1 works out of test_uint32
    test_uint32 = std::numeric_limits<std::uint32_t>::max();

    unsigned int get1;

    // All bits in bitfield1 are set so the first i bits should equal
    // std::pow(2, i) - 1 when interpreted as an integer
    for (unsigned int i = 0; i <= 32; ++i)
    {
        unsigned int get1 = 0;
        bitfield1.getBitsAsNumericType(get1, 0, i);
        std::cout << get1 << " ";
        MUST_BE_TRUE(get1 == std::pow(2, i) - 1);
    }
    std::cout << "\n";

    // Least significant bit of each byte is set
    memset(&test_uint32, 1, 4);

    // Grab the first of the set bits.
    bitfield1.getBitsAsNumericType(get1, 0, 1);
    MUST_BE_TRUE(get1 == 1); // 2^1

    // Grab all the way up to the second of the set bits.
    bitfield1.getBitsAsNumericType(get1, 0, 9);
    MUST_BE_TRUE(get1 == 257); // 2^9 - 2^8 + previous answer

    // This is purposefully grabbing more than the three set bits.  Extra
    // grabbed bits should be zero and shouldn't affect the result.
    bitfield1.getBitsAsNumericType(get1, 0, 18);
    MUST_BE_TRUE(get1 == 65793); // 2^17 - 2^16 + previous answer

    // Purposefully grabbing more than the four set bits.  Extra grabbed bits
    // should be zero and shouldn't affect the result.
    bitfield1.getBitsAsNumericType(get1, 0, 30);
    MUST_BE_TRUE(get1 == 16843009); // 2^25 - 2^24 + previous answer

    // SETBITSASNUMERICTYPE TESTED BELOW

    // We're once again going to use bitfield1 to write to test_uint32 memory
    test_uint32 = 0;

    std::uint32_t set1 = 0;

    for (unsigned int i = 0; i <= 32; ++i)
    {
        set1 = static_cast<std::uint32_t>(std::pow(2, i) - 1);
        std::cout << set1 << " ";

        bitfield1.setBitsAsNumericType(set1, 0, i);
        MUST_BE_TRUE(test_uint32 == set1);
    }
    std::cout << "\n";

    test_uint32 = 0;

    // Set the first of the bits.
    set1 = 0b1;
    bitfield1.setBitsAsNumericType(set1, 0, 1);
    MUST_BE_TRUE(test_uint32 == 1); // 2^1

    // Set all the way up to the second of the set bits.
    set1 = 0b100000001;
    bitfield1.setBitsAsNumericType(set1, 0, 9);
    MUST_BE_TRUE(test_uint32 == 257); // 2^9 - 2^8 + previous answer

    // This is purposefully setting more than the three set bits.  Extra set
    // bits should be zero and shouldn't affect the result.
    set1 = 0b10000000100000001;
    bitfield1.setBitsAsNumericType(set1, 0, 18);
    MUST_BE_TRUE(test_uint32 == 65793); // 2^17 - 2^16 + previous answer

    // Purposefully setting more than the four set bits.  Extra set bits should
    // be zero and shouldn't affect the result.
    set1 = 0b1000000010000000100000001;
    bitfield1.setBitsAsNumericType(set1, 0, 30);
    MUST_BE_TRUE(test_uint32 == 16843009); // 2^25 - 2^24 + previous answer

    return Test::PASSED;
}
