#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "MacAddress_test.hpp"

#include "MacAddress.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(MacAddress_test);

//==============================================================================
void MacAddress_test::addTestCases()
{
    ADD_TEST_CASE(Operators);
}

//==============================================================================
void MacAddress_test::Operators::addTestCases()
{
    ADD_TEST_CASE(EqualTo);
    ADD_TEST_CASE(NotEqualTo);
}

//==============================================================================
Test::Result MacAddress_test::Operators::EqualTo::body()
{
    std::vector<std::string> mac_addresses;
    mac_addresses.push_back("00:00:00:00:00:00");
    mac_addresses.push_back("11:22:33:44:55:66");
    mac_addresses.push_back("aa:bb:cc:dd:ee:ff");
    mac_addresses.push_back("ff:ff:ff:ff:ff:ff");

    // Check all MAC addresses against each other
    for (unsigned int i = 0; i < mac_addresses.size(); i++)
    {
        MacAddress mac_address_i(mac_addresses[i]);

        for (unsigned int j = 0; j < mac_addresses.size(); j++)
        {
            if (i != j)
            {
                continue;
            }

            MacAddress mac_address_j(mac_addresses[j]);

            if (i == j)
            {
                MUST_BE_TRUE(mac_address_i == mac_address_j);
                MUST_BE_TRUE(mac_address_i == mac_addresses[j]);
                MUST_BE_TRUE(mac_address_j == mac_addresses[i]);
                MUST_BE_TRUE(mac_addresses[i] == mac_address_j);
                MUST_BE_TRUE(mac_addresses[j] == mac_address_i);
            }
        }
    }

    return Test::PASSED;
}

//==============================================================================
Test::Result MacAddress_test::Operators::NotEqualTo::body()
{
    std::vector<std::string> mac_addresses;
    mac_addresses.push_back("00:00:00:00:00:00");
    mac_addresses.push_back("11:22:33:44:55:66");
    mac_addresses.push_back("aa:bb:cc:dd:ee:ff");
    mac_addresses.push_back("ff:ff:ff:ff:ff:ff");

    // Check all MAC addresses against each other
    for (unsigned int i = 0; i < mac_addresses.size(); i++)
    {
        MacAddress mac_address(mac_addresses[i]);

        MUST_BE_TRUE(mac_address == mac_address);
        MUST_BE_TRUE(mac_address == mac_addresses[i]);
        MUST_BE_TRUE(mac_addresses[i] == mac_address);
    }

    return Test::PASSED;
}
