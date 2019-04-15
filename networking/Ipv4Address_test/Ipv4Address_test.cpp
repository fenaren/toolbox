#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "Ipv4Address.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_PROGRAM_BEGIN(Ipv4Address_test)
TEST(Operators_EqualityInequality)
TEST(Constructor_ReadRaw)
TEST(WriteRaw)
TEST_CASES_PROGRAM_END(Ipv4Address_test)

//==============================================================================
void Ipv4Address_test::addTestCases()
{
    addTestCase(new Operators_EqualityInequality());
    addTestCase(new Constructor_ReadRaw());
    addTestCase(new WriteRaw());
}

//==============================================================================
Test::Result Ipv4Address_test::Operators_EqualityInequality::body()
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

    return Test::PASSED;
}

//==============================================================================
Test::Result Ipv4Address_test::Constructor_ReadRaw::body()
{
    std::uint8_t raw_ipv4[] = {97, 98, 99, 100};
    Ipv4Address ipv4(raw_ipv4);

    for (unsigned int i = 0; i < Ipv4Address::LENGTH_BYTES; ++i)
    {
        MUST_BE_TRUE(ipv4.getByte(i) == raw_ipv4[i]);
    }

    return Test::PASSED;
}

//==============================================================================
Test::Result Ipv4Address_test::WriteRaw::body()
{
    Ipv4Address ipv4;
    std::uint8_t raw_ipv4[Ipv4Address::LENGTH_BYTES];

    for (unsigned int i = 0; i < Ipv4Address::LENGTH_BYTES; ++i)
    {
        raw_ipv4[i] = 0;
        ipv4.setByte(i, i);
    }

    ipv4.DataField::writeRaw(raw_ipv4);

    for (unsigned int i = 0; i < Ipv4Address::LENGTH_BYTES; ++i)
    {
        MUST_BE_TRUE(raw_ipv4[i] == i);
    }

    return Test::PASSED;
}
