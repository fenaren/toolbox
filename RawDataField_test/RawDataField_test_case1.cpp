#include <cstring>

#include "RawDataField.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

TEST_HEADER(RawDataField_test_case1);
TEST_CONSTRUCTOR_DESTRUCTOR(RawDataField_test_case1);

//==============================================================================
Test::Result RawDataField_test_case1::body()
{
    // Makes no sense to create an bit field of 0 bytes but we should test
    // it here
    unsigned int test_bf2_len = 10;
    RawDataField test_bf1(0, misc::BYTES); // Dynamic allocation
    RawDataField test_bf2(test_bf2_len, misc::BYTES);
    RawDataField test_bf3(test_bf2);     // Tests the copy constructor

    unsigned int test_data_len = 20;
    unsigned char test_data[test_data_len];
    for (unsigned int i = 0; i < test_data_len; i++)
    {
        test_data[i] = static_cast<unsigned char>(i);
    }

    // Tests getLengthBytes
    RawDataField test_bf4(
        test_data, test_data_len, misc::BYTES, false);
    MUST_BE_TRUE(test_bf4.getLengthBytes() == test_data_len);

    // Tests writeRaw
    unsigned char test_data2[test_data_len];
    test_bf4.DataField::writeRaw(test_data2);
    MUST_BE_TRUE(memcmp(test_data, test_data2, test_data_len) == 0);

    // Tests readRaw, equality, inequality
    RawDataField test_bf5(test_data_len, misc::BYTES);
    test_bf5.DataField::readRaw(test_data2);
    MUST_BE_TRUE(test_bf4 == test_bf5);
    MUST_BE_FALSE(test_bf4 != test_bf5);

    // Tests assignment
    memset(test_data,  0, test_data_len);
    memset(test_data2, 1, test_data_len);
    RawDataField test_bf6(
        test_data2, test_data_len, misc::BYTES, false);
    test_bf4 = test_bf6;
    MUST_BE_TRUE(memcmp(test_data, test_data2, test_data_len) == 0);

    return Test::PASSED;
}
