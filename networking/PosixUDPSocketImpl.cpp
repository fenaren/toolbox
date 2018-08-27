#include <cstdio>
#include <cstring>
#include <errno.h>
#include <netdb.h>
#include <stdexcept>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#if defined DEBUG
#include <iostream>
#endif

#include "PosixUDPSocketImpl.hpp"

#include "PosixSocketCommon.hpp"

//==============================================================================
// Initializes platform-specific UDP socket
//==============================================================================
PosixUDPSocketImpl::PosixUDPSocketImpl() :
    blocking_timeout(0.0)
{
    // Create the socket
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    // Check for errors
    if (socket_fd == -1)
    {
        throw std::runtime_error(strerror(errno));
    }

    int bcast = 1;

    // Enable broadcasting by default
    if (setsockopt(
            socket_fd, SOL_SOCKET, SO_BROADCAST, &bcast, sizeof(bcast)) == -1)
    {
#if defined DEBUG
        perror("PosixUDPSocketImpl::PosixUDPSocketImpl");
#endif
    }
}

//==============================================================================
// Shuts down this socket
//==============================================================================
PosixUDPSocketImpl::~PosixUDPSocketImpl()
{
    PosixSocketCommon::shutdown(socket_fd);
}

//==============================================================================
// Enables blocking
//==============================================================================
bool PosixUDPSocketImpl::enableBlocking()
{
    return PosixSocketCommon::enableBlocking(socket_fd);
}

//==============================================================================
// Disables blocking
//==============================================================================
bool PosixUDPSocketImpl::disableBlocking()
{
    return PosixSocketCommon::disableBlocking(socket_fd);
}

//==============================================================================
// Returns whether or not this socket can block
//==============================================================================
bool PosixUDPSocketImpl::isBlockingEnabled()
{
    return PosixSocketCommon::isBlockingEnabled(socket_fd);
}

//==============================================================================
// Binds this socket to a local address
//==============================================================================
bool PosixUDPSocketImpl::bind(unsigned int& port)
{
    return PosixSocketCommon::bind(socket_fd, local_address, port);
}

//==============================================================================
// Reads data from socket into buffer
//==============================================================================
int PosixUDPSocketImpl::read(unsigned char* buffer, unsigned int size)
{
    return PosixSocketCommon::read(
        socket_fd,
        buffer,
        size,
        blocking_timeout,
        reinterpret_cast<sockaddr*>(&peer_address),
        sizeof(sockaddr_in));
}

//==============================================================================
// Writes data from buffer into socket
//==============================================================================
int PosixUDPSocketImpl::write(const unsigned char* buffer, unsigned int size)
{
    return PosixSocketCommon::write(
        socket_fd,
        buffer,
        size,
        blocking_timeout,
        reinterpret_cast<sockaddr*>(&sendto_address),
        sizeof(sockaddr_in));
}

//==============================================================================
// Sets the destination datagrams are sent to
//==============================================================================
bool PosixUDPSocketImpl::sendTo(const std::string& address, unsigned int port)
{
    // Create some hints for getaddrinfo
    addrinfo hints;
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    hints.ai_flags    = 0;

    // Will point to the results list
    addrinfo* results = 0;

    // Loop up the provided hostname
    int ret = getaddrinfo(address.c_str(), 0, &hints, &results);

    // Check for errors
    if (ret != 0)
    {
#if defined DEBUG
        std::cerr << "PosixUDPSocketImpl::sendTo: " << gai_strerror(ret) << "\n";
#endif
        return false;
    }

    // If there weren't any results just error and leave
    if (!results)
    {
#if defined DEBUG
        std::cerr << "Address not usable\n";
#endif
        return false;
    }

    // If anything was found just choose the first one; if anything more
    // complicated is needed it'll be implemented later

#if defined DEBUG
    // Warn if we got more than one return
    if (results->ai_next)
    {
        std::cerr << "PosixUDPSocketImpl::connect: Multiple addrinfo results "
                  << "returned, arbitrarily choosing the first one\n";
    }
#endif
    memcpy(&sendto_address, results->ai_addr, sizeof(sockaddr_in));
    sendto_address.sin_port = htons(port);

    // Release addrinfo memory back to the kernel; freeaddrinfo returns nothing
    // so no need to check for errors here
    freeaddrinfo(results);

    return true;
}

//==============================================================================
// Clears all the data out of this socket's receive buffer
//==============================================================================
void PosixUDPSocketImpl::clearBuffer()
{
    PosixSocketCommon::clearBuffer(
        socket_fd,
        reinterpret_cast<sockaddr*>(&peer_address),
        sizeof(sockaddr_in));
}
