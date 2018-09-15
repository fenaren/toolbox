#include <iostream>
#include <string.h>

#include "TCPSocket.hpp"

bool case1()
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
        return false;
    }

    std::cout << "Using port " << port << "\n";

    if (!socket2.listen())
    {
        return false;
    }

    // As long as this goes out to localhost it should be almost instantaneous,
    // at least in human terms
    if (!socket1.connect("localhost", port))
    {
        return false;
    }

    // SEND SOMETHING ONE WAY

    if (!socket2.accept())
    {
        return false;
    }

    socket2.enableBlocking();

    if (socket1.write(send1, send_size) != send_size)
    {
        return false;
    }

    if (socket2.read(send1_recv, send_size) != send_size)
    {
        return false;
    }

    std::cout << "Sent " << send1 << " received " << send1_recv << "\n";
    if (memcmp(send1, send1_recv, send_size))
    {
        return false;
    }

    // SEND SOMETHING BACK

    if (socket2.write(send2, send_size) != send_size)
    {
        return false;
    }

    if (socket1.read(send2_recv, send_size) != send_size)
    {
        return false;
    }

    std::cout << "Sent " << send2 << " received " << send2_recv << "\n";
    if (memcmp(send2, send2_recv, send_size))
    {
        return false;
    }

    return true;
}

int case2()
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
        return false;
    }

    std::cout << "Using port " << port << "\n";

    if (!socket2.listen())
    {
        return false;
    }

    // As long as this goes out to localhost it should be almost instantaneous,
    // at least in human terms
    if (!socket1.connect("localhost", port))
    {
        return false;
    }

    // SEND SOMETHING ONE WAY

    TCPSocket* socket3 = socket2.accept(false);
    if (!socket3)
    {
        return false;
    }

    socket3->enableBlocking();

    if (socket1.write(send1, send_size) != send_size)
    {
        return false;
    }

    if (socket3->read(send1_recv, send_size) != send_size)
    {
        return false;
    }

    std::cout << "Sent " << send1 << " received " << send1_recv << "\n";
    if (memcmp(send1, send1_recv, send_size))
    {
        return false;
    }

    // SEND SOMETHING BACK

    if (socket3->write(send2, send_size) != send_size)
    {
        return false;
    }

    if (socket1.read(send2_recv, send_size) != send_size)
    {
        return false;
    }

    std::cout << "Sent " << send2 << " received " << send2_recv << "\n";
    if (memcmp(send2, send2_recv, send_size))
    {
        return false;
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
        return false;
    }

    TCPSocket* socket5 = socket2.accept(false);
    if (!socket5)
    {
        return false;
    }

    socket5->enableBlocking();

    if (socket4.write(send1, send_size) != send_size)
    {
        return false;
    }

    if (socket5->read(send1_recv, send_size) != send_size)
    {
        return false;
    }

    std::cout << "Sent " << send1 << " received " << send1_recv << "\n";
    if (memcmp(send1, send1_recv, send_size))
    {
        return false;
    }

    // SEND SOMETHING BACK

    if (socket5->write(send2, send_size) != send_size)
    {
        return false;
    }

    if (socket4.read(send2_recv, send_size) != send_size)
    {
        return false;
    }

    std::cout << "Sent " << send2 << " received " << send2_recv << "\n";
    if (memcmp(send2, send2_recv, send_size))
    {
        return false;
    }

    delete socket5;

    return true;
}

int main(int argc, char** argv)
{
    return !(case1() && case2());
}
