#include <iostream>

#include "MacAddress.hpp"

int main (int argc, char** argv)
{
    MacAddress mac_address;
    std::cout << mac_address << "\n";
    std::cout << mac_address[1] << "\n";
    mac_address[1] = 'q';
    std::cout << mac_address[1] << "\n";
    return 0;
}
