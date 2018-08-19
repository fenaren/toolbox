#include "Ipv4Address.hpp"
#include "MacAddress.hpp"

namespace miscNetworking
{
    bool getMacAddress(const std::string& interface_name,
                       MacAddress&        mac_address);

    bool getIpv4Address(const std::string& interface_name,
                        Ipv4Address&       ipv4_address);
}
