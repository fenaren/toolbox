#include <cmath>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <iostream>

#include "BitField.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_HEADER(BitField_test_case2);
TEST_CONSTRUCTOR_DESTRUCTOR(BitField_test_case2);

template<class T> bool tryAllBits(BitField& bitfield, T& raw_bitfield);

//==============================================================================
Test::Result BitField_test_case2::body()
{
    std::uint8_t  raw_bitfield1 = 0;
    std::uint16_t raw_bitfield2 = 0;
    std::uint32_t raw_bitfield4 = 0;

    BitField bitfield1(&raw_bitfield1, BITS_PER_BYTE, false);
    BitField bitfield2(reinterpret_cast<std::uint8_t*>(&raw_bitfield2),
                       sizeof(std::uint16_t) * BITS_PER_BYTE,
                       false);
    BitField bitfield4(reinterpret_cast<std::uint8_t*>(&raw_bitfield4),
                       sizeof(std::uint32_t) * BITS_PER_BYTE,
                       false);

    // Make sure trying to get out-of-range bits properly throws an exception
    bool exception_caught = false;
    try
    {
        bitfield1.getBit(BITS_PER_BYTE);
    }
    catch (std::out_of_range& ex)
    {
        exception_caught = true;
    }
    MUST_BE_TRUE(exception_caught);

    // Test all the bits in a couple differnt size bitfields
    MUST_BE_TRUE(tryAllBits(bitfield1, raw_bitfield1));
    MUST_BE_TRUE(tryAllBits(bitfield2, raw_bitfield2));
    MUST_BE_TRUE(tryAllBits(bitfield4, raw_bitfield4));

    return Test::PASSED;
}

//==============================================================================
template<class T> bool tryAllBits(BitField& bitfield, T& raw_bitfield)
{
    bool all_good = true;

    for (unsigned int i = 0; i < sizeof(T) * BITS_PER_BYTE; i++)
    {
        bitfield.setBit(i, true);
        all_good = raw_bitfield == std::round(std::pow(2, i));
        if (!all_good) break;

        std::cout << raw_bitfield << " ";

        bitfield.setBit(i, false);
        all_good = raw_bitfield == 0;
        if (!all_good) break;
    }

    std::cout << "\n";

    return all_good;
}
