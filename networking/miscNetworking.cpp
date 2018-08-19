#include "miscNetworking.hpp"

#include "Ipv4Address.hpp"
#include "MacAddress.hpp"

namespace miscNetworking
{
    bool getMacAddress(const std::string& interface_name,
                       MacAddress&        mac_address)
    {
        // Getting MAC and IP addresses requires a socket, doesn't matter what
        // kind
        int sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
        if (sock_fd == -1)
        {
            // If something goes wrong, print an error message and quit
            perror(0);
            shutdown();
        }

        // Fill out an ifreq with name of the target interface
        ifreq iface;
        strcpy(iface.ifr_name, interface_name.c_str());

        // Request our MAC address
        if (ioctl(sock_fd, SIOCGIFHWADDR, &iface) == -1)
        {
            // If something goes wrong, print an error message and quit
            perror(0);
            shutdown();
        }

        // Initialize own_mac
        memcpy(own_mac, iface.ifr_hwaddr.sa_data, 6);
    }

    bool getIpv4Address(const std::string& interface_name,
                        Ipv4Address&       ipv4_address)
    {
        // Request our IP address
        if (ioctl(sock_fd, SIOCGIFADDR, &iface) == -1)
        {
            // If something goes wrong, print an error message and quit
            perror(0);
            shutdown();
        }

        // Initialize own IP address
        sockaddr_in* temp_addr = (sockaddr_in*)&iface.ifr_addr;
        memcpy(own_ip, (const void*)(&(temp_addr->sin_addr.s_addr)), 4);

        // Not needed anymore; return code not useful enough to bother with
        close(sock_fd);
    }
}
