#include <iostream>
#include <string>
#include <vector>

#include "MacAddress.hpp"

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

    // Initialize vector of test MAC addresses; THESE MUST ALL BE UNIQUE
    std::vector<std::string> unique_mac_addresses;

    unique_mac_addresses.push_back("00:00:00:00:00:00");
    unique_mac_addresses.push_back("11:22:33:44:55:66");
    unique_mac_addresses.push_back("aa:bb:cc:dd:ee:ff");
    unique_mac_addresses.push_back("ff:ff:ff:ff:ff:ff");

    if (fail_on_purpose)
    {
        // Add a duplicate MAC address; this will be detected below and the test
        // should fail
        std::cout << "FAILING ON PURPOSE, adding duplicate MAC address\n";
        unique_mac_addresses.push_back(unique_mac_addresses[0]);
    }

    // Failed cases are recorded here and output at the end of the test
    std::vector<std::pair<unsigned int, unsigned int> > failed_cases;

    // Check all MAC addresses against each other
    for (unsigned int i = 0; i < unique_mac_addresses.size(); i++)
    {
        MacAddress mac_address_i(unique_mac_addresses[i]);

        std::string mac_address_i_str;
        mac_address_i.toString(mac_address_i_str);

        // Exercise output stream functionality by outputting each MacAddress
        std::cout << mac_address_i << "\n";

        for (unsigned int j = 0; j < unique_mac_addresses.size(); j++)
        {
            MacAddress mac_address_j(unique_mac_addresses[j]);

            std::string mac_address_j_str;
            mac_address_j.toString(mac_address_j_str);

            if (i == j)
            {
                if (!(mac_address_i == mac_address_j &&
                      mac_address_i_str == mac_address_j_str &&
                      mac_address_i == unique_mac_addresses[j] &&
                      mac_address_j == unique_mac_addresses[i] &&
                      unique_mac_addresses[i] == mac_address_j &&
                      unique_mac_addresses[j] == mac_address_i))
                {
                    failed_cases.push_back(
                        std::pair<unsigned int, unsigned int>(i, j));
                }
            }
            else
            {
                if (!(mac_address_i != mac_address_j &&
                      mac_address_i_str != mac_address_j_str &&
                      mac_address_i != unique_mac_addresses[j] &&
                      mac_address_j != unique_mac_addresses[i] &&
                      unique_mac_addresses[i] != mac_address_j &&
                      unique_mac_addresses[j] != mac_address_i))
            {
                    failed_cases.push_back(
                        std::pair<unsigned int, unsigned int>(i, j));
                }
            }
        }
    }

    std::cout << "Failed cases: " << failed_cases.size() << "\n";

    for (unsigned int i = 0; i < failed_cases.size(); i++)
    {
        std::cout << unique_mac_addresses[failed_cases[i].first] << " and "
                  << unique_mac_addresses[failed_cases[i].second] << "\n";
    }

    // This unit test passes if no failed cases were recorded; remember that a
    // zero return value means success
    return failed_cases.size() != 0;
}
