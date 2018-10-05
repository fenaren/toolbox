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

    // Byteswaps the buffer of memory at "buffer" of length "len".  For example
    // a "len" value of 4 would be used for swapping a single 32-bit integer
    void byteswap(unsigned char* buffer, unsigned int len);
}

#endif
