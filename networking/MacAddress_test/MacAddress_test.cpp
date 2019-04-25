#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "MacAddress.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_PROGRAM_BEGIN(MacAddress_test)
TEST(Operators_EqualityInequality)
TEST_CASES_PROGRAM_END(MacAddress_test)

//==============================================================================
void MacAddress_test::addTestCases()
{
    addTestCase(new Operators_EqualityInequality());
}

//==============================================================================
Test::Result MacAddress_test::Operators_EqualityInequality::body()
{
    // Initialize vector of test MAC addresses; THESE MUST ALL BE UNIQUE
    std::vector<std::string> unique_mac_addresses;

    unique_mac_addresses.push_back("00:00:00:00:00:00");
    unique_mac_addresses.push_back("11:22:33:44:55:66");
    unique_mac_addresses.push_back("aa:bb:cc:dd:ee:ff");
    unique_mac_addresses.push_back("ff:ff:ff:ff:ff:ff");

    // Failed cases are recorded here and output at the end of the test
    std::vector<std::pair<unsigned int, unsigned int> > failed_eqineq_cases;

    // Check all MAC addresses against each other
    for (unsigned int i = 0; i < unique_mac_addresses.size(); i++)
    {
        MacAddress mac_address_i(unique_mac_addresses[i]);

        // Exercise output stream functionality by outputting each MacAddress
        std::cout << mac_address_i << "\n";

        for (unsigned int j = 0; j < unique_mac_addresses.size(); j++)
        {
            MacAddress mac_address_j(unique_mac_addresses[j]);

            if (i == j)
            {
                if (!(mac_address_i == mac_address_j &&
                      // cppcheck-suppress duplicateExpression
                      mac_address_i == unique_mac_addresses[j] &&
                      // cppcheck-suppress duplicateExpression
                      mac_address_j == unique_mac_addresses[i] &&
                      unique_mac_addresses[i] == mac_address_j &&
                      unique_mac_addresses[j] == mac_address_i))
                {
                    failed_eqineq_cases.push_back(
                        std::pair<unsigned int, unsigned int>(i, j));
                }
            }
            else
            {
                if (!(mac_address_i != mac_address_j &&
                      // cppcheck-suppress duplicateExpression
                      mac_address_i != unique_mac_addresses[j] &&
                      // cppcheck-suppress duplicateExpression
                      mac_address_j != unique_mac_addresses[i] &&
                      unique_mac_addresses[i] != mac_address_j &&
                      unique_mac_addresses[j] != mac_address_i))
            {
                    failed_eqineq_cases.push_back(
                        std::pair<unsigned int, unsigned int>(i, j));
                }
            }
        }
    }

    for (unsigned int i = 0; i < failed_eqineq_cases.size(); i++)
    {
        std::cout << unique_mac_addresses[failed_eqineq_cases[i].first]
                  << " and "
                  << unique_mac_addresses[failed_eqineq_cases[i].second]
                  << "\n";
    }

    MUST_BE_TRUE(failed_eqineq_cases.empty());

    return Test::PASSED;
}
