#include <cstring>
#include <iostream>

#include "TCPSocket.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_HEADER(TCPSocket_test_case1);
TEST_CONSTRUCTOR_DESTRUCTOR(TCPSocket_test_case1);

//==============================================================================
Test::Result TCPSocket_test_case1::body()
{
    unsigned int port = 0;  // Use whatever port is available

    unsigned char send1[]      = {'o',  'n',  'e',  '\0'};
    unsigned char send1_recv[] = {'\0', '\0', '\0', '\0'};
    unsigned char send2[]      = {'t',  'w',  'o',  '\0'};
    unsigned char send2_recv[] = {'\0', '\0', '\0', '\0'};
    int send_size = 4;  // Must equal the length of all four arrays

    TCPSocket socket1;
    TCPSocket socket2;

    socket2.disableBlocking();

    if (!socket2.bind(port))
    {
        return Test::FAILED;
    }

    std::cout << "Using port " << port << "\n";

    if (!socket2.listen())
    {
        return Test::FAILED;
    }

    // As long as this goes out to localhost it should be almost instantaneous,
    // at least in human terms
    if (!socket1.connect("localhost", port))
    {
        return Test::FAILED;
    }

    // SEND SOMETHING ONE WAY

    if (!socket2.accept())
    {
        return Test::FAILED;
    }

    socket2.enableBlocking();

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
