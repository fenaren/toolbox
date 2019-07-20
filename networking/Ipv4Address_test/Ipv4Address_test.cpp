#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "Ipv4Address_test.hpp"

#include "Ipv4Address.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Ipv4Address_test);

//==============================================================================
void Ipv4Address_test::addTestCases()
{
    ADD_TEST_CASE(Operators);
}

//==============================================================================
void Ipv4Address_test::Operators::addTestCases()
{
    ADD_TEST_CASE(EqualTo);
    ADD_TEST_CASE(NotEqualTo);
}

//==============================================================================
Test::Result Ipv4Address_test::Operators::EqualTo::body()
{
    std::vector<std::string> ipv4_addresses;
    ipv4_addresses.push_back("0.0.0.0");
    ipv4_addresses.push_back("1.2.3.4");
    ipv4_addresses.push_back("1.2.200.210");
    ipv4_addresses.push_back("01.02.200.201");
    ipv4_addresses.push_back("192.168.1.1");
    ipv4_addresses.push_back("255.255.255.255");

    for (unsigned int i = 0; i < ipv4_addresses.size(); i++)
    {
        Ipv4Address ipv4_address(ipv4_addresses[i]);

        MUST_BE_TRUE(ipv4_address      == ipv4_address);
        MUST_BE_TRUE(ipv4_address      == ipv4_addresses[i]);
        MUST_BE_TRUE(ipv4_addresses[i] == ipv4_address);
    }

    return Test::PASSED;
}

//==============================================================================
Test::Result Ipv4Address_test::Operators::NotEqualTo::body()
{
    std::vector<std::string> ipv4_addresses;
    ipv4_addresses.push_back("0.0.0.0");
    ipv4_addresses.push_back("1.2.3.4");
    ipv4_addresses.push_back("1.2.200.210");
    ipv4_addresses.push_back("01.02.200.201");
    ipv4_addresses.push_back("192.168.1.1");
    ipv4_addresses.push_back("255.255.255.255");

    for (unsigned int i = 0; i < ipv4_addresses.size(); i++)
    {
        Ipv4Address ipv4_address_i(ipv4_addresses[i]);

        for (unsigned int j = 0; j < ipv4_addresses.size(); j++)
        {
            if (i == j)
            {
                continue;
            }

            Ipv4Address ipv4_address_j(ipv4_addresses[j]);

            MUST_BE_TRUE(ipv4_address_i    != ipv4_address_j);
            MUST_BE_TRUE(ipv4_address_i    != ipv4_addresses[j]);
            MUST_BE_TRUE(ipv4_address_j    != ipv4_addresses[i]);
            MUST_BE_TRUE(ipv4_addresses[i] != ipv4_address_j);
            MUST_BE_TRUE(ipv4_addresses[j] != ipv4_address_i);
        }
    }

    return Test::PASSED;
}
