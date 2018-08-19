#include <iostream>

#include "Ipv4Address.hpp"
#include "MacAddress.hpp"
#include "miscNetworking.hpp"

int main(int argc, char** argv)
{
    MacAddress en0_mac;
    if (!miscNetworking::getMacAddress("en0", en0_mac))
    {
        return 1;
    }

    std::cout << en0_mac << "\n";

    return 0;
}
