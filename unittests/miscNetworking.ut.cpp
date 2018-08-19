#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "Ipv4Address.hpp"
#include "MacAddress.hpp"
#include "miscNetworking.hpp"

int main(int argc, char** argv)
{
    std::string interface_name;
    std::string command;

    char from_pipe[MacAddress::MAC_MAX_STR_LENGTH_CHARS];
    memset(from_pipe, 0, MacAddress::MAC_MAX_STR_LENGTH_CHARS);

    // First get the MAC address using the command line

    MacAddress mac_cmdline;

#if defined MACOS

    interface_name = "en0";

    command = "ifconfig | grep -A 1 ";
    command += interface_name;
    command += " | grep ether | cut -f 2 | cut -d \" \" -f 2\n";
    std::FILE* fd = popen(command.c_str(), "r");
    std::fread(from_pipe, 1, MacAddress::MAC_MAX_STR_LENGTH_CHARS - 1, fd);
    fclose(fd);
    mac_cmdline = from_pipe;

#elif defined LINUX

    interface_name = "p119p1";

#endif

    std::cout << mac_cmdline << " for \"" << interface_name << "\" from "
              << "command line\n";

    // Now get a MAC address using miscNetworking
    MacAddress mac_getmacaddress;
    if (!miscNetworking::getMacAddress(interface_name, mac_getmacaddress))
    {
        std::cerr << "Could not use getMacAddress to retrieve MAC address "
                  << "for \"" << interface_name << "\"\n";
        return 1;
    }

    std::cout << mac_getmacaddress << " for \"" << interface_name
              << "\" from getMacAddress\n";

    // Do the two MAC addresses match?
    return !(mac_cmdline == mac_getmacaddress);
}
