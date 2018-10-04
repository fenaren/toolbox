#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "miscNetworking_test_case1.hpp"

#include "MacAddress.hpp"
#include "miscNetworking.hpp"

//==============================================================================
miscNetworking_test_case1::miscNetworking_test_case1()
{
}

//==============================================================================
miscNetworking_test_case1::~miscNetworking_test_case1()
{
}

//==============================================================================
Test::Result miscNetworking_test_case1::run()
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
        return Test::SKIPPED;
    }

    command += " | grep ether | cut -f 6 -d \" \"\n";
    std::FILE* fd = popen(command.c_str(), "r");

    std::size_t num_read =
        std::fread(
            from_pipe, 1, MacAddress::MAX_STR_LENGTH_CHARS - 1, fd);
    pclose(fd);

    if (num_read != MacAddress::MAX_STR_LENGTH_CHARS - 1)
    {
        return Test::FAILED;
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
        return Test::FAILED;
    }

    std::cout << mac_getmacaddress << " for \"" << interface_name
              << "\" from getMacAddress\n";

    // Do the two MAC addresses match?
    if (mac_cmdline == mac_getmacaddress)
    {
        return Test::PASSED;
    }

    return Test::FAILED;

#else

    return Test::SKIPPED;

#endif
}
