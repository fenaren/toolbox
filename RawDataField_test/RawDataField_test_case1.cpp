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
    unsigned int test_rdf2_len = 10;
    RawDataField test_rdf1(0, misc::BYTES); // Dynamic allocation
    RawDataField test_rdf2(test_rdf2_len, misc::BYTES);
    RawDataField test_rdf3(test_rdf2);     // Tests the copy constructor

    unsigned int test_data_len = 20;
    unsigned char test_data[test_data_len];
    for (unsigned int i = 0; i < test_data_len; i++)
    {
        test_data[i] = static_cast<unsigned char>(i);
    }

    // Tests getLengthBytes
    RawDataField test_rdf4(
        test_data, test_data_len, misc::BYTES, false);
    MUST_BE_TRUE(test_rdf4.getLengthBytes() == test_data_len);

    // Tests writeRaw
    unsigned char test_data2[test_data_len];
    test_rdf4.DataField::writeRaw(test_data2);
    MUST_BE_TRUE(memcmp(test_data, test_data2, test_data_len) == 0);

    // Tests readRaw, equality, inequality
    RawDataField test_rdf5(test_data_len, misc::BYTES);
    test_rdf5.DataField::readRaw(test_data2);
    MUST_BE_TRUE(test_rdf4 == test_rdf5);
    MUST_BE_FALSE(test_rdf4 != test_rdf5);

    // Tests getByte, setByte
    for (unsigned int i = 0; i < test_data_len; i++)
    {
        MUST_BE_TRUE(test_data[i] == test_rdf4.getByte(i));

        test_rdf4.setByte(i, 0);
        MUST_BE_TRUE(test_data[i] == 0);
    }

    // Tests assignment
    memset(test_data,  0, test_data_len);
    memset(test_data2, 1, test_data_len);
    RawDataField test_rdf6(
        test_data2, test_data_len, misc::BYTES, false);
    test_rdf4 = test_rdf6;
    MUST_BE_TRUE(memcmp(test_data, test_data2, test_data_len) == 0);

    return Test::PASSED;
}
