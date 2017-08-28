#include <iostream>

#include "MacAddress.hpp"

int main (int argc, char** argv)
{
    // Will be set to false if any test case fails
    bool passed = true;

    // TEST CASE 1

    MacAddress mac_address1;

    bool result = mac_address1 == mac_address1;
    std::cout << "MAC address equals itself: " << result << "\n";
    if (!result) passed = false;

    // TEST CASE 2

    MacAddress mac_address2(mac_address1);
    mac_address2[1] = 'a';
    mac_address2[2] = 'b';

    result = mac_address1 != mac_address2;
    std::cout << "MAC address does not equal a different MAC address: "
              << result << "\n";
    if (!result) passed = false;

    // TEST CASE 3

    MacAddress mac_address3;
    std::cin >> mac_address3;

    MacAddress mac_address4("11:22:33:44:55:66");

    result = mac_address3 == mac_address4;
    std::cout << mac_address3 << " equals " << mac_address4 << ": " << result
              << "\n";
    if (!result) passed = false;

    return !passed;
}
