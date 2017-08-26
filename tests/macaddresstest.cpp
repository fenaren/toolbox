#include <iostream>

#include "MacAddress.hpp"

int main (int argc, char** argv)
{
    MacAddress mac_address1;
    std::cout << mac_address1 << "\n";

    std::cout << (mac_address1 == mac_address1) << "\n";

    MacAddress mac_address2(mac_address1);
    mac_address2[1] = 'a';
    mac_address2[2] = 'b';
    std::cout << mac_address2 << "\n";

    std::cout << (mac_address1 == mac_address2) << "\n";

    MacAddress mac_address3;
    std::cin >> mac_address3;
    std::cout << mac_address3 << "\n";
    return 0;
}
