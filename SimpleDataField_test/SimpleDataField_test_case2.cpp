#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

#include "SimpleDataField.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

TEST_HEADER(SimpleDataField_test_case2);
TEST_CONSTRUCTOR_DESTRUCTOR(SimpleDataField_test_case2);

//==============================================================================
template <class T>
bool writeRawTest(unsigned int                     offset_bits,
                  const std::vector<std::uint8_t>& shouldbe)
{
    SimpleDataField<T> test_sdf_uchar(0);

    std::uint8_t test_sdf_uchar_buf[sizeof(T) + 1];
    memset(test_sdf_uchar_buf, 0xff, sizeof(T) + 1);
    test_sdf_uchar.writeRaw(
        test_sdf_uchar_buf, misc::getByteOrder(), offset_bits);

    bool all_match = true;
    for (unsigned int i = 0; i < sizeof(T) + 1; ++i)
    {
        std::cout << static_cast<unsigned int>(test_sdf_uchar_buf[i]) << " ";
        if (test_sdf_uchar_buf[i] != shouldbe[i])
        {
            all_match = false;
            std::cout << "(WRONG should be "
                      << static_cast<unsigned int>(shouldbe[i]) << ") ";
        }
    }
    std::cout << "\n";

    return all_match;
}

//==============================================================================
Test::Result SimpleDataField_test_case2::body()
{
    for (unsigned int i = 0; i <= BITS_PER_BYTE; ++i)
    {
        MUST_BE_TRUE(
            writeRawTest<unsigned char>(
                i,
                std::vector<std::uint8_t>(
                    {static_cast<std::uint8_t>(std::pow(2, i) - 1),
                     static_cast<std::uint8_t>(255 - (std::pow(2, i) - 1))})));
    }

    return Test::PASSED;
}
