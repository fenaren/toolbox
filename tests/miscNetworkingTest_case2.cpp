#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "miscNetworkingTest_case2.hpp"

#include "Ipv4Address.hpp"
#include "miscNetworking.hpp"

//==============================================================================
miscNetworkingTest_case2::miscNetworkingTest_case2()
{
}

//==============================================================================
miscNetworkingTest_case2::~miscNetworkingTest_case2()
{
}

//==============================================================================
Test::Result miscNetworkingTest_case2::run()
{
// This will only work on a POSIX-compatible system
#if defined LINUX or MACOS

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

    // Check here to see if we can even run this test successfully
    if (system(command.c_str()) != 0)
    {
        return Test::SKIPPED;
    }

    command += " | grep inet | cut -f 6 -d \" \"\n";
    std::FILE* fd = popen(command.c_str(), "r");

    std::size_t num_read =
        std::fread(
            from_pipe, 1, Ipv4Address::IPV4_MAX_STR_LENGTH_CHARS - 1, fd);
    fclose(fd);

    if (num_read != Ipv4Address::IPV4_MAX_STR_LENGTH_CHARS - 1)
    {
        return Test::FAILED;
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
        return Test::FAILED;
    }

    std::cout << ipv4_getipv4address << " for \"" << interface_name
              << "\" from getIpv4Address\n";

    // Do the two MAC addresses match?
    if (ipv4_cmdline == ipv4_getipv4address)
    {
        return Test::PASSED;
    }

    return Test::FAILED;

#else

    return Test::SKIPPED;

#endif
}
