#include <iostream>
#include <string>

#include "Ipv4Address.hpp"
#include "MacAddress.hpp"
#include "miscNetworking.hpp"

int main(int argc, char** argv)
{
    std::string interface_name;
#if defined MACOS
    interface_name = "en0";
#elif defined LINUX
    interface_name = "p119p1";
#endif

    MacAddress mac_address;
    if (!miscNetworking::getMacAddress(interface_name, mac_address))
    {
        std::cerr << "Could not retrieve MAC address for \"" << interface_name
                  << "\"\n";
        return 1;
    }

    std::cout << mac_address << "\n";

    return 0;
}
