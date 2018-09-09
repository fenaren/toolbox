#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "Ipv4Address.hpp"

int main(int argc, char** argv)
{
    // We can fail this test (return non-zero) on purpose if we explicitly ask
    // for it, useful for testing the test harness
    bool fail_on_purpose = false;

    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "-F")
        {
            fail_on_purpose = true;
        }
    }

    // Initialize vector of test IPv4 addresses; THESE MUST ALL BE UNIQUE
    std::vector<std::string> unique_ipv4_addresses;

    unique_ipv4_addresses.push_back("0.0.0.0");
    unique_ipv4_addresses.push_back("1.2.3.4");
    unique_ipv4_addresses.push_back("1.2.200.210");
    unique_ipv4_addresses.push_back("01.02.200.201");
    unique_ipv4_addresses.push_back("192.168.1.1");
    unique_ipv4_addresses.push_back("255.255.255.255");

    if (fail_on_purpose)
    {
        // Add a duplicate IPv4 address; this will be detected below and the test
        // should fail
        std::cout << "FAILING ON PURPOSE, adding duplicate IPv4 address\n";
        unique_ipv4_addresses.push_back(unique_ipv4_addresses[0]);
    }

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
                      ipv4_address_i == unique_ipv4_addresses[j] &&
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
                      ipv4_address_i != unique_ipv4_addresses[j] &&
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
    testipv42.write(testcipv42);
    bool write_success =
        memcmp(testcipv42, shouldbe, Ipv4Address::LENGTH_BYTES) == 0;
    if (!write_success)
    {
        std::cout << "Write test failed\n";
    }

    std::string testipv42str = testipv42;
    std::cout << testipv42str << "\n";

    // This unit test passes if no failed cases were recorded; remember that a
    // zero return value means success
    return !(failed_eqineq_cases.size() == 0 && read_success && write_success);
}
