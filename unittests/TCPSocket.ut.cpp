#include <iostream>
#include <string.h>

#include "TCPSocket.hpp"

int main(int argc, char** argv)
{
    unsigned int port = 0;  // Use whatever port is available

    char send1[]      = {'o',  'n',  'e',  '\0'};
    char send1_recv[] = {'\0', '\0', '\0', '\0'};
    char send2[]      = {'t',  'w',  'o',  '\0'};
    char send2_recv[] = {'\0', '\0', '\0', '\0'};
    unsigned int send_size = 4;  // Must equal the length of all four arrays

    TCPSocket socket1;
    TCPSocket socket2;

    socket2.disableBlocking();

    if (!socket2.bind(port))
    {
        return 1;
    }

    std::cout << "Using port " << port << "\n";

    if (!socket2.listen())
    {
        return 1;
    }

    // As long as this goes out to localhost it should be almost instantaneous,
    // at least in human terms
    if (!socket1.connect("localhost", port))
    {
        return 1;
    }

    // SEND SOMETHING ONE WAY

    if (!socket2.accept())
    {
        return 1;
    }

    socket2.enableBlocking();

    if (socket1.write(send1, send_size) != send_size)
    {
        return 1;
    }

    if (socket2.read(send1_recv, send_size) != send_size)
    {
        return 1;
    }

    std::cout << "Sent " << send1 << " received " << send1_recv << "\n";
    if (memcmp(send1, send1_recv, send_size))
    {
        return 1;
    }

    // SEND SOMETHING BACK

    if (socket2.write(send2, send_size) != send_size)
    {
        return 1;
    }

    if (socket1.read(send2_recv, send_size) != send_size)
    {
        return 1;
    }

    std::cout << "Sent " << send2 << " received " << send2_recv << "\n";
    if (memcmp(send2, send2_recv, send_size))
    {
        return 1;
    }

    return 0;
}
