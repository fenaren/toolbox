#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "Ipv4Address.hpp"
#include "MacAddress.hpp"
#include "miscNetworking.hpp"

int case1()
{

// This will work only on POSIX-compatible systems
#if defined LINUX or MACOS

    std::string interface_name;
    std::string command;

    char from_pipe[MacAddress::MAX_STR_LENGTH_CHARS];
    memset(from_pipe, 0, MacAddress::MAX_STR_LENGTH_CHARS);

    // First get the MAC address using the command line

    MacAddress mac_cmdline;

/*  This is a potential macOS unit test
    interface_name = "en0";

    command = "ifconfig | grep -A 1 ";
    command += interface_name;
    command += " | grep ether | cut -f 2 | cut -d \" \" -f 2\n";
    std::FILE* fd = popen(command.c_str(), "r");
    std::fread(from_pipe, 1, MacAddress::MAX_STR_LENGTH_CHARS - 1, fd);
    fclose(fd);
    mac_cmdline = from_pipe;
*/

    interface_name = "p119p1";

    command = "ip addr | grep -A 1 ";
    command += interface_name;

    // Check here to see if we can even run this test successfully
    if (system(command.c_str()) != 0)
    {
        return 2;
    }

    command += " | grep ether | cut -f 6 -d \" \"\n";
    std::FILE* fd = popen(command.c_str(), "r");

    std::size_t num_read =
        std::fread(
            from_pipe, 1, MacAddress::MAX_STR_LENGTH_CHARS - 1, fd);
    fclose(fd);

    if (num_read != MacAddress::MAX_STR_LENGTH_CHARS - 1)
    {
        return 1;
    }

    mac_cmdline = from_pipe;

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

#else

    return 2;

#endif
}

int case2()
{

// This will only work on a POSIX-compatible system
#if defined LINUX or MACOS

    std::string interface_name;
    std::string command;

    char from_pipe[Ipv4Address::MAX_STR_LENGTH_CHARS];
    memset(from_pipe, 0, Ipv4Address::MAX_STR_LENGTH_CHARS);

    // First get the MAC address using the command line

    Ipv4Address ipv4_cmdline;

/*  This is a potential macOS unit test
    interface_name = "en0";

    command = "ifconfig | grep -A 2 ";
    command += interface_name;
    command += " | grep inet | cut -f 2 | cut -d \" \" -f 2\n";
    std::FILE* fd = popen(command.c_str(), "r");
    std::fread(from_pipe, 1, Ipv4Address::MAX_STR_LENGTH_CHARS - 1, fd);
    fclose(fd);
    ipv4_cmdline = from_pipe;
*/

    interface_name = "p119p1";

    command = "ip addr | grep -A 2 ";
    command += interface_name;

    // Check here to see if we can even run this test successfully
    if (system(command.c_str()) != 0)
    {
        return 2;
    }

    command += " | grep inet | cut -f 6 -d \" \"\n";
    std::FILE* fd = popen(command.c_str(), "r");

    std::size_t num_read =
        std::fread(
            from_pipe, 1, Ipv4Address::MAX_STR_LENGTH_CHARS - 1, fd);
    fclose(fd);

    if (num_read != Ipv4Address::MAX_STR_LENGTH_CHARS - 1)
    {
        return 1;
    }

    ipv4_cmdline = from_pipe;

    std::cout << ipv4_cmdline << " for \"" << interface_name << "\" from "
              << "command line\n";

    // Now get a IPv4 address using miscNetworking
    Ipv4Address ipv4_getipv4address;
    if (!miscNetworking::getIpv4Address(interface_name, ipv4_getipv4address))
    {
        std::cerr << "Could not use getIpv4Address to retrieve IPv4 address "
                  << "for \"" << interface_name << "\"\n";
        return 1;
    }

    std::cout << ipv4_getipv4address << " for \"" << interface_name
              << "\" from getIpv4Address\n";

    // Do the two MAC addresses match?
    return !(ipv4_cmdline == ipv4_getipv4address);

#else

    return 2;

#endif
}

int main(int argc, char** argv)
{
#if defined LINUX or MACOS
    int return_case1 = case1();
    int return_case2 = case2();

    // If any case was skipped then consider the whole test skipped
    if (return_case1 == 2 || return_case2 == 2)
    {
        return 2;
    }
    // If any case failed consider the whole test failed
    else if (return_case1 == 1 || return_case2 == 1)
    {
        return 1;
    }

    return 0;
#else
    return 2;
#endif
}
