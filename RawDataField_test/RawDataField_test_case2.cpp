#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <iostream>

#include "RawDataField.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

TEST_HEADER(RawDataField_test_case2);
TEST_CONSTRUCTOR_DESTRUCTOR(RawDataField_test_case2);

template<class T> bool tryAllBits(RawDataField& rdf, T& number);

//==============================================================================
Test::Result RawDataField_test_case2::body()
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

    // Make sure trying to get out-of-range bits properly throws an exception
    bool exception_caught = false;
    try
    {
        number_rdf1.getBit(BITS_PER_BYTE);
    }
    catch (std::out_of_range& ex)
    {
        exception_caught = true;
    }
    MUST_BE_TRUE(exception_caught);

    // Test all the bits in a couple differnt size integers
    MUST_BE_TRUE(tryAllBits(number_rdf1, number1));
    MUST_BE_TRUE(tryAllBits(number_rdf2, number2));
    MUST_BE_TRUE(tryAllBits(number_rdf4, number4));

    // Switch the bit indexing mode and try again
    number_rdf1.setBitIndexingMode(RawDataField::MS_LEAST);
    number_rdf2.setBitIndexingMode(RawDataField::MS_LEAST);
    number_rdf4.setBitIndexingMode(RawDataField::MS_LEAST);
    MUST_BE_TRUE(tryAllBits(number_rdf1, number1));
    MUST_BE_TRUE(tryAllBits(number_rdf2, number2));
    MUST_BE_TRUE(tryAllBits(number_rdf4, number4));

    return Test::PASSED;
}

//==============================================================================
template<class T> bool tryAllBits(RawDataField& number_rdf, T& number)
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
