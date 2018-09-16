#include <iostream>
#include <string.h>

#include "UDPSocketTest.hpp"

#include "Test.hpp"
#include "TestProgramMain.hpp"
#include "UDPSocket.hpp"

TEST_PROGRAM_MAIN(UDPSocketTest);

//==============================================================================
UDPSocketTest::UDPSocketTest()
{
}

//==============================================================================
UDPSocketTest::~UDPSocketTest()
{
}

//==============================================================================
Test::Result UDPSocketTest::run()
{
    unsigned int port1 = 0;  // Use whatever port is available
    unsigned int port2 = 0;  // Use whatever port is available

    unsigned char send1[]      = {'o',  'n',  'e',  '\0'};
    unsigned char send1_recv[] = {'\0', '\0', '\0', '\0'};
    unsigned char send2[]      = {'t',  'w',  'o',  '\0'};
    unsigned char send2_recv[] = {'\0', '\0', '\0', '\0'};
    int send_size = 4;  // Must equal the length of all four arrays

    UDPSocket socket1;
    UDPSocket socket2;

    if (!socket1.bind(port1))
    {
        return Test::FAILED;
    }

    if (!socket2.bind(port2))
    {
        return Test::FAILED;
    }

    std::cout << "Socket1 using port " << port1 << "\n";
    std::cout << "Socket2 using port " << port2 << "\n";

    // As long as this goes out to localhost it should be almost instantaneous,
    // at least in human terms
    if (!socket1.sendTo("localhost", port2))
    {
        return Test::FAILED;
    }

    if (!socket2.sendTo("localhost", port1))
    {
        return Test::FAILED;
    }

    // SEND SOMETHING ONE WAY

    if (socket1.write(send1, send_size) != send_size)
    {
        return Test::FAILED;
    }

    if (socket2.read(send1_recv, send_size) != send_size)
    {
        return Test::FAILED;
    }

    std::cout << "Sent " << send1 << " received " << send1_recv << "\n";
    if (memcmp(send1, send1_recv, send_size))
    {
        return Test::FAILED;
    }

    // SEND SOMETHING BACK

    if (socket2.write(send2, send_size) != send_size)
    {
        return Test::FAILED;
    }

    if (socket1.read(send2_recv, send_size) != send_size)
    {
        return Test::FAILED;
    }

    std::cout << "Sent " << send2 << " received " << send2_recv << "\n";
    if (memcmp(send2, send2_recv, send_size))
    {
        return Test::FAILED;
    }

    return Test::PASSED;
}
