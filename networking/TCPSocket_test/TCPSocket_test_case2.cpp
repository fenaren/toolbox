#include <cstring>
#include <iostream>

#include "TCPSocket.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_HEADER(TCPSocket_test_case2);
TEST_CONSTRUCTOR_DESTRUCTOR(TCPSocket_test_case2);

//==============================================================================
Test::Result TCPSocket_test_case2::body()
{
    unsigned int port = 0;  // Use whatever port is available

    unsigned char send1[]      = {'a',  'b',  'c',  '\0'};
    unsigned char send1_recv[] = {'\0', '\0', '\0', '\0'};
    unsigned char send2[]      = {'d',  'e',  'f',  '\0'};
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

    TCPSocket* socket3 = socket2.accept(false);
    if (!socket3)
    {
        return Test::FAILED;
    }

    socket3->enableBlocking();

    if (socket1.write(send1, send_size) != send_size)
    {
        return Test::FAILED;
    }

    if (socket3->read(send1_recv, send_size) != send_size)
    {
        return Test::FAILED;
    }

    std::cout << "Sent " << send1 << " received " << send1_recv << "\n";
    if (memcmp(send1, send1_recv, send_size))
    {
        return Test::FAILED;
    }

    // SEND SOMETHING BACK

    if (socket3->write(send2, send_size) != send_size)
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

    // Have to do this here to shut the socket down so we can open another one
    // below
    delete socket3;

    // Reset the receiving arrays
    memset(send1_recv, 0, 4);
    memset(send2_recv, 0, 4);

    TCPSocket socket4;

    // As long as this goes out to localhost it should be almost instantaneous,
    // at least in human terms
    if (!socket4.connect("localhost", port))
    {
        return Test::FAILED;
    }

    TCPSocket* socket5 = socket2.accept(false);
    if (!socket5)
    {
        return Test::FAILED;
    }

    socket5->enableBlocking();

    if (socket4.write(send1, send_size) != send_size)
    {
        return Test::FAILED;
    }

    if (socket5->read(send1_recv, send_size) != send_size)
    {
        return Test::FAILED;
    }

    std::cout << "Sent " << send1 << " received " << send1_recv << "\n";
    if (memcmp(send1, send1_recv, send_size))
    {
        return Test::FAILED;
    }

    // SEND SOMETHING BACK

    if (socket5->write(send2, send_size) != send_size)
    {
        return Test::FAILED;
    }

    if (socket4.read(send2_recv, send_size) != send_size)
    {
        return Test::FAILED;
    }

    std::cout << "Sent " << send2 << " received " << send2_recv << "\n";
    if (memcmp(send2, send2_recv, send_size))
    {
        return Test::FAILED;
    }

    delete socket5;

    return Test::PASSED;
}
