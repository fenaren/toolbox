#if !defined MISC_NETWORKING_HPP
#define MISC_NETWORKING_HPP

#include <string>

#include "Ipv4Address.hpp"
#include "MacAddress.hpp"

namespace miscNetworking
{
    // Retrieves the MAC address corresponding to the given interface name
    bool getMacAddress(const std::string& interface_name,
                       MacAddress&        mac_address);

    // Retrieves an IP address corresponding to the given interface name
    bool getIpv4Address(const std::string& interface_name,
                        Ipv4Address&       ipv4_address);
}

#endif
