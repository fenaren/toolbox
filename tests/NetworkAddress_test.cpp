#include <cstring>

#include "NetworkAddress_test.hpp"

#include "NetworkAddress.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(NetworkAddress_test);

//==============================================================================
NetworkAddress_test::NetworkAddress_test()
{
}

//==============================================================================
NetworkAddress_test::~NetworkAddress_test()
{
}

//==============================================================================
Test::Result NetworkAddress_test::run()
{
    // Makes no sense to create an network address of 0 bytes but we should test
    // it here
    unsigned int test_na2_len = 10;
    NetworkAddress test_na1(0);            // Dynamic allocation
    NetworkAddress test_na2(test_na2_len); // Dynamic allocation
    NetworkAddress test_na3(test_na2);     // Tests the copy constructor

    unsigned int test_data_len = 20;
    unsigned char test_data[test_data_len];
    for (unsigned int i = 0; i < test_data_len; i++)
    {
        test_data[i] = static_cast<unsigned char>(i);
    }

    // Tests getLengthBytes
    NetworkAddress test_na4(test_data, test_data_len);
    MUST_BE_TRUE(test_na4.getLengthBytes() == test_data_len);

    // Tests writeRaw
    unsigned char test_data2[test_data_len];
    test_na4.writeRaw(test_data2);
    MUST_BE_TRUE(memcmp(test_data, test_data2, test_data_len) == 0);

    // Tests readRaw, equality, inequality
    NetworkAddress test_na5(test_data_len);
    test_na5.readRaw(test_data2);
    MUST_BE_TRUE(test_na4 == test_na5);
    MUST_BE_FALSE(test_na4 != test_na5);

    // Tests getOctet, setOctet
    for (unsigned int i = 0; i < test_data_len; i++)
    {
        MUST_BE_TRUE(test_data[i] == test_na4.getOctet(i));

        test_na4.setOctet(i, 0);
        MUST_BE_TRUE(test_data[i] == 0);
    }

    // Tests assignment
    memset(test_data,  0, test_data_len);
    memset(test_data2, 1, test_data_len);
    NetworkAddress test_na6(test_data2, test_data_len);
    test_na4 = test_na6;
    MUST_BE_TRUE(memcmp(test_data, test_data2, test_data_len) == 0);

    return Test::PASSED;
}
