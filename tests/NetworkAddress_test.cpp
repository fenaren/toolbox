#include <cstring>

#include "NetworkAddress_test.hpp"

#include "NetworkAddress.hpp"
#include "Test.hpp"
#include "TestProgramMain.hpp"

TEST_PROGRAM_MAIN(NetworkAddress_test);

#define MUST_BE_TRUE(expression) \
    if (!(expression))           \
    {                            \
        return Test::FAILED;     \
    }

#define MUST_BE_FALSE(expression) \
    if (expression)               \
    {                             \
        return Test::FAILED;      \
    }

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
    NetworkAddress test_na1(0);         // Dynamic allocation
    NetworkAddress test_na2(10);        // Dynamic allocation
    NetworkAddress test_na3(test_na2);  // Tests the copy constructor

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

    // Tests equality and inequality
    NetworkAddress test_na5(test_data2, test_data_len);
    MUST_BE_TRUE(test_na4 == test_na5);
    MUST_BE_FALSE(test_na4 != test_na5);

    // Tests getOctet, setOctet
    for (unsigned int i = 0; i < test_data_len; i++)
    {
        MUST_BE_TRUE(test_data[i] == test_na4.getOctet(i));

        test_na4.setOctet(i, 0);
        MUST_BE_TRUE(test_data[i] == 0);
    }

    return Test::PASSED;
}
