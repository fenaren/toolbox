#include <iostream>
#include <string>
#include <vector>

#include "MacAddress.hpp"

int main(int argc, char** argv)
{
    // Initialize vector of test MAC addresses; EACH ELEMENT MUST CONTAIN A
    // UNIQUE MAC ADDRESS, NO DUPLICATES ALLOWED
    std::vector<MacAddress> mac_address;

    mac_address.push_back(MacAddress("11:22:33:44:55:66"));
    mac_address.push_back(MacAddress("aa:bb:cc:dd:ee:ee"));
    mac_address.push_back(MacAddress("00:00:00:00:00:00"));
//    mac_address.push_back(MacAddress("ff:ff:ff:ff:ff:ff"));
//    mac_address.push_back(MacAddress("ff:ff:ff:ff:ff:ff"));

    // Failed cases are recorded here and output at the end of the test
    std::vector<std::pair<unsigned int, unsigned int> > failed_cases;

    // Check all MAC addresses against each other
    for (unsigned int i = 0; i < mac_address.size(); i++)
    {
        std::cout << mac_address[i] << "\n";
        for (unsigned int j = 0; j < mac_address.size(); j++)
        {
            // If differing MAC addresses are being compared, test for
            // inequality, otherwise test for equality
            if ((mac_address[i] == mac_address[j] && i != j) ||
                (mac_address[i] != mac_address[j] && i == j))
            {
                failed_cases.push_back(
                    std::pair<unsigned int, unsigned int>(i, j));
            }
        }
    }

    std::cout << "Failed cases: " << failed_cases.size() << "\n";

    for (unsigned int i = 0; i < failed_cases.size(); i++)
    {
        std::cout << mac_address[failed_cases[i].first] << " and "
                  << mac_address[failed_cases[i].second] << "\n";
    }

    // This unit test passes if no failed cases were recorded
    return failed_cases.size() == 0;
}
