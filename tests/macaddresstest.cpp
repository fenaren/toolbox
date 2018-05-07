#include <iostream>
#include <string>
#include <vector>

#include "MacAddress.hpp"

int main(int argc, char** argv)
{
    // Initialize vector of test MAC addresses; THESE MUST ALL BE UNIQUE
    std::vector<MacAddress> unique_mac_addresses;

    unique_mac_addresses.push_back(MacAddress());
    unique_mac_addresses.push_back(MacAddress("11:22:33:44:55:66"));
    unique_mac_addresses.push_back(MacAddress("aa:bb:cc:dd:ee:ff"));
    unique_mac_addresses.push_back(MacAddress("ff:ff:ff:ff:ff:ff"));

    // Failed cases are recorded here and output at the end of the test
    std::vector<std::pair<unsigned int, unsigned int> > failed_cases;

    // Check all MAC addresses against each other
    for (unsigned int i = 0; i < unique_mac_addresses.size(); i++)
    {
        // Exercise output stream functionality
        std::cout << unique_mac_addresses[i] << "\n";

        for (unsigned int j = 0; j < unique_mac_addresses.size(); j++)
        {
            std::string mac_address_i;
            unique_mac_addresses[i].toString(mac_address_i);

            std::string mac_address_j;
            unique_mac_addresses[j].toString(mac_address_j);

            if (i == j)
            {
                if (unique_mac_addresses[i] != unique_mac_addresses[j] ||
                    mac_address_i != mac_address_j)
                {
                    failed_cases.push_back(
                        std::pair<unsigned int, unsigned int>(i, j));
                }
            }
            else
            {
                if (unique_mac_addresses[i] == unique_mac_addresses[j] ||
                    mac_address_i == mac_address_j)
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

    // This unit test passes if no failed cases were recorded
    return failed_cases.size() == 0;
}
