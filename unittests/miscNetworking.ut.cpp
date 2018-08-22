#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "Ipv4Address.hpp"
#include "MacAddress.hpp"
#include "miscNetworking.hpp"

bool case1()
{
    // Only run case 1 if we're on Linux; case 1 tests getMacAddress, which at
    // this moment will only work on Linux (getMacAddress isn't implemented for
    // Windows and macOS

#if defined LINUX
    std::string interface_name;
    std::string command;

    char from_pipe[MacAddress::MAC_MAX_STR_LENGTH_CHARS];
    memset(from_pipe, 0, MacAddress::MAC_MAX_STR_LENGTH_CHARS);

    // First get the MAC address using the command line

    MacAddress mac_cmdline;

/*  This is a potential macOS unit test
    interface_name = "en0";

    command = "ifconfig | grep -A 1 ";
    command += interface_name;
    command += " | grep ether | cut -f 2 | cut -d \" \" -f 2\n";
    std::FILE* fd = popen(command.c_str(), "r");
    std::fread(from_pipe, 1, MacAddress::MAC_MAX_STR_LENGTH_CHARS - 1, fd);
    fclose(fd);
    mac_cmdline = from_pipe;
*/

    interface_name = "p119p1";

    command = "ip addr | grep -A 1 ";
    command += interface_name;
    command += " | grep ether | cut -f 6 -d \" \"\n";
    std::FILE* fd = popen(command.c_str(), "r");
    std::fread(from_pipe, 1, MacAddress::MAC_MAX_STR_LENGTH_CHARS - 1, fd);
    fclose(fd);
    mac_cmdline = from_pipe;

    std::cout << mac_cmdline << " for \"" << interface_name << "\" from "
              << "command line\n";

    // Now get a MAC address using miscNetworking
    MacAddress mac_getmacaddress;
    if (!miscNetworking::getMacAddress(interface_name, mac_getmacaddress))
    {
        std::cerr << "Could not use getMacAddress to retrieve MAC address "
                  << "for \"" << interface_name << "\"\n";
        return false;
    }

    std::cout << mac_getmacaddress << " for \"" << interface_name
              << "\" from getMacAddress\n";

    // Do the two MAC addresses match?
    return mac_cmdline == mac_getmacaddress;
#else
    return true;
#endif
}

int case2()
{
    // Only run case 2 if we're on Linux; case 2 tests getIpv4Address, which at
    // this moment will only work on Linux (getIpv4Address isn't implemented for
    // Windows and macOS

#if defined LINUX
    std::string interface_name;
    std::string command;

    char from_pipe[Ipv4Address::IPV4_MAX_STR_LENGTH_CHARS];
    memset(from_pipe, 0, Ipv4Address::IPV4_MAX_STR_LENGTH_CHARS);

    // First get the MAC address using the command line

    Ipv4Address ipv4_cmdline;

/*  This is a potential macOS unit test
    interface_name = "en0";

    command = "ifconfig | grep -A 2 ";
    command += interface_name;
    command += " | grep inet | cut -f 2 | cut -d \" \" -f 2\n";
    std::FILE* fd = popen(command.c_str(), "r");
    std::fread(from_pipe, 1, Ipv4Address::IPV4_MAX_STR_LENGTH_CHARS - 1, fd);
    fclose(fd);
    ipv4_cmdline = from_pipe;
*/

    interface_name = "p119p1";

    command = "ip addr | grep -A 2 ";
    command += interface_name;
    command += " | grep inet | cut -f 6 -d \" \"\n";
    std::FILE* fd = popen(command.c_str(), "r");
    std::fread(from_pipe, 1, Ipv4Address::IPV4_MAX_STR_LENGTH_CHARS - 1, fd);
    fclose(fd);
    ipv4_cmdline = from_pipe;

    std::cout << ipv4_cmdline << " for \"" << interface_name << "\" from "
              << "command line\n";

    // Now get a IPv4 address using miscNetworking
    Ipv4Address ipv4_getipv4address;
    if (!miscNetworking::getIpv4Address(interface_name, ipv4_getipv4address))
    {
        std::cerr << "Could not use getIpv4Address to retrieve IPv4 address "
                  << "for \"" << interface_name << "\"\n";
        return false;
    }

    std::cout << ipv4_getipv4address << " for \"" << interface_name
              << "\" from getIpv4Address\n";

    // Do the two MAC addresses match?
    return ipv4_cmdline == ipv4_getipv4address;
#else
    return true;
#endif
}

int main(int argc, char** argv)
{
    return !(case1() && case2());
}
