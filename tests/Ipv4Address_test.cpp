#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "Ipv4Address_test.hpp"

#include "Ipv4Address.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Ipv4Address_test);

//==============================================================================
Ipv4Address_test::Ipv4Address_test()
{
}

//==============================================================================
Ipv4Address_test::~Ipv4Address_test()
{
}

//==============================================================================
Test::Result Ipv4Address_test::run()
{
    // Initialize vector of test IPv4 addresses; THESE MUST ALL BE UNIQUE
    std::vector<std::string> unique_ipv4_addresses;

    unique_ipv4_addresses.push_back("0.0.0.0");
    unique_ipv4_addresses.push_back("1.2.3.4");
    unique_ipv4_addresses.push_back("1.2.200.210");
    unique_ipv4_addresses.push_back("01.02.200.201");
    unique_ipv4_addresses.push_back("192.168.1.1");
    unique_ipv4_addresses.push_back("255.255.255.255");

    // Failed cases are recorded here and output at the end of the test
    std::vector<std::pair<unsigned int, unsigned int> > failed_eqineq_cases;

    // Check all IPv4 addresses against each other
    for (unsigned int i = 0; i < unique_ipv4_addresses.size(); i++)
    {
        Ipv4Address ipv4_address_i(unique_ipv4_addresses[i]);

        // Exercise output stream functionality by outputting each Ipv4Address
        std::cout << ipv4_address_i << "\n";

        for (unsigned int j = 0; j < unique_ipv4_addresses.size(); j++)
        {
            Ipv4Address ipv4_address_j(unique_ipv4_addresses[j]);

            if (i == j)
            {
                if (!(ipv4_address_i == ipv4_address_j &&
                      // cppcheck-suppress duplicateExpression
                      ipv4_address_i == unique_ipv4_addresses[j] &&
                      // cppcheck-suppress duplicateExpression
                      ipv4_address_j == unique_ipv4_addresses[i] &&
                      unique_ipv4_addresses[i] == ipv4_address_j &&
                      unique_ipv4_addresses[j] == ipv4_address_i))
                {
                    failed_eqineq_cases.push_back(
                        std::pair<unsigned int, unsigned int>(i, j));
                }
            }
            else
            {
                if (!(ipv4_address_i != ipv4_address_j &&
                      // cppcheck-suppress duplicateExpression
                      ipv4_address_i != unique_ipv4_addresses[j] &&
                      // cppcheck-suppress duplicateExpression
                      ipv4_address_j != unique_ipv4_addresses[i] &&
                      unique_ipv4_addresses[i] != ipv4_address_j &&
                      unique_ipv4_addresses[j] != ipv4_address_i))
            {
                    failed_eqineq_cases.push_back(
                        std::pair<unsigned int, unsigned int>(i, j));
                }
            }
        }
    }

    std::cout << "Failed equality/inequality cases: "
              << failed_eqineq_cases.size() << "\n";

    for (unsigned int i = 0; i < failed_eqineq_cases.size(); i++)
    {
        std::cout << unique_ipv4_addresses[failed_eqineq_cases[i].first]
                  << " and "
                  << unique_ipv4_addresses[failed_eqineq_cases[i].second]
                  << "\n";
    }

    // Test the read function
    unsigned char testcipv41[] = {97, 98, 99, 100};
    Ipv4Address testipv41(testcipv41);
    bool read_success = testipv41 == "97.98.99.100";
    if (!read_success)
    {
        std::cout << "Read test failed\n";
    }

    std::string testipv41str = testipv41;
    std::cout << testipv41str << "\n";

    // Test the write function
    std::string testipv4str = "1.2.3.4";
    Ipv4Address testipv42(testipv4str);
    unsigned char testcipv42[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    char shouldbe[] = {1, 2, 3, 4};
    testipv42.writeRaw(testcipv42);
    bool write_success =
        memcmp(testcipv42, shouldbe, Ipv4Address::LENGTH_BYTES) == 0;
    if (!write_success)
    {
        std::cout << "Write test failed\n";
    }

    std::string testipv42str = testipv42;
    std::cout << testipv42str << "\n";

    // This unit test passes if no failed cases were recorded
    if (failed_eqineq_cases.size() == 0 &&
        read_success &&
        write_success)
    {
        return Test::PASSED;
    }

    return Test::FAILED;
}
