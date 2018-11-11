#include <cstring>

#include "BitField.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TRIVIAL_TEST(BitField_test);

//==============================================================================
Test::Result BitField_test::run()
{
    // Makes no sense to create an bit field of 0 bytes but we should test
    // it here
    unsigned int test_bf2_len = 10;
    BitField test_bf1(0);            // Dynamic allocation
    BitField test_bf2(test_bf2_len); // Dynamic allocation
    BitField test_bf3(test_bf2);     // Tests the copy constructor

    unsigned int test_data_len = 20;
    unsigned char test_data[test_data_len];
    for (unsigned int i = 0; i < test_data_len; i++)
    {
        test_data[i] = static_cast<unsigned char>(i);
    }

    // Tests getLengthBytes
    BitField test_bf4(test_data, test_data_len, false);
    MUST_BE_TRUE(test_bf4.getLengthBytes() == test_data_len);

    // Tests writeRaw
    unsigned char test_data2[test_data_len];
    test_bf4.writeRaw(test_data2);
    MUST_BE_TRUE(memcmp(test_data, test_data2, test_data_len) == 0);

    // Tests readRaw, equality, inequality
    BitField test_bf5(test_data_len);
    test_bf5.readRaw(test_data2);
    MUST_BE_TRUE(test_bf4 == test_bf5);
    MUST_BE_FALSE(test_bf4 != test_bf5);

    // Tests getOctet, setOctet
    for (unsigned int i = 0; i < test_data_len; i++)
    {
        MUST_BE_TRUE(test_data[i] == test_bf4.getOctet(i));

        test_bf4.setOctet(i, 0);
        MUST_BE_TRUE(test_data[i] == 0);
    }

    // Tests assignment
    memset(test_data,  0, test_data_len);
    memset(test_data2, 1, test_data_len);
    BitField test_bf6(test_data2, test_data_len, false);
    test_bf4 = test_bf6;
    MUST_BE_TRUE(memcmp(test_data, test_data2, test_data_len) == 0);

    return Test::PASSED;
}
