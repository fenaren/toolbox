#include <cstring>
#include <errno.h>
#include <iostream>
#include <netdb.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "LinuxUDPSocketImpl.hpp"

#include "LinuxSocketCommon.hpp"

//====================================================================
// Initializes platform-specific UDP socket
//====================================================================
LinuxUDPSocketImpl::LinuxUDPSocketImpl()
{
    blocking_timeout = -1.0;

    ts_blocking_timeout.tv_sec =  0;
    ts_blocking_timeout.tv_nsec = 0;

    // Create the socket
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    // Check for errors
    if (socket_fd == -1)
    {
        perror("LinuxUDPSocketImpl::LinuxUDPSocketImpl");
        return;
    }

    int bcast = 1;

    // Enable broadcasting by default
    if (setsockopt(socket_fd,
                   SOL_SOCKET,
                   SO_BROADCAST,
                   &bcast,
                   sizeof(bcast)) == -1)
    {
        perror("LinuxUDPSocketImpl::LinuxUDPSocketImpl");
    }
}

//====================================================================
// Shuts down this socket
//====================================================================
LinuxUDPSocketImpl::~LinuxUDPSocketImpl()
{
    LinuxSocketCommon::shutdown(socket_fd);
}

//====================================================================
// Enables blocking
//====================================================================
bool LinuxUDPSocketImpl::enableBlocking()
{
    return LinuxSocketCommon::enableBlocking(socket_fd);
}

//====================================================================
// Disables blocking
//====================================================================
bool LinuxUDPSocketImpl::disableBlocking()
{
    return LinuxSocketCommon::disableBlocking(socket_fd);
}

//====================================================================
// Returns whether or not this socket can block
//====================================================================
bool LinuxUDPSocketImpl::isBlockingEnabled()
{
    return LinuxSocketCommon::isBlockingEnabled(socket_fd);
}

//====================================================================
// Sets blocking timeout
//====================================================================
void LinuxUDPSocketImpl::setBlockingTimeout(double blocking_timeout)
{
    LinuxSocketCommon::setBlockingTimeout(blocking_timeout,
                                          this->blocking_timeout,
                                          ts_blocking_timeout);
}

//====================================================================
// Gets blocking timeout
//====================================================================
double LinuxUDPSocketImpl::getBlockingTimeout() const
{
    return blocking_timeout;
}

//====================================================================
// Binds this socket to a local address
//====================================================================
bool LinuxUDPSocketImpl::bind(unsigned int port)
{
    // Set up local address info to bind with
    local_address.sin_family      = AF_INET;
    local_address.sin_port        = htons(port);
    local_address.sin_addr.s_addr = 0;

    // Do the bind
    if (::bind(socket_fd, (sockaddr*)&local_address, sizeof(sockaddr_in)) == -1)
    {
        perror("LinuxUDPSocketImpl::bind");
        return false;
    }

    return true;
}

//====================================================================
// Reads data from socket into buffer
//====================================================================
int LinuxUDPSocketImpl::read(char* buffer, unsigned int size)
{
    return LinuxSocketCommon::read(
        socket_fd,
        buffer,
        size,
        blocking_timeout,
        ts_blocking_timeout,
        reinterpret_cast<sockaddr*>(&peer_address),
        sizeof(sockaddr_in));
}

//====================================================================
// Writes data from buffer into socket
//====================================================================
int LinuxUDPSocketImpl::write(const char* buffer, unsigned int size)
{
    return LinuxSocketCommon::write(
        socket_fd,
        buffer,
        size,
        blocking_timeout,
        ts_blocking_timeout,
        reinterpret_cast<sockaddr*>(&sendto_address),
        sizeof(sockaddr_in));
}

//====================================================================
// Sets the destination datagrams are sent to
//====================================================================
bool LinuxUDPSocketImpl::sendTo(const std::string& address, unsigned int port)
{
    // Create some hints for getaddrinfo
    addrinfo hints;
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = 0;
    hints.ai_flags    = 0;

    // Will point to the results list
    addrinfo* results = 0;

    // Loop up the provided hostname
    int ret = getaddrinfo(address.c_str(), 0, &hints, &results);

    // Check for errors
    if (ret != 0)
    {
        std::cerr << "LinuxUDPSocketImpl::sendTo: " << gai_strerror(ret) << "\n";
        return false;
    }

    // If there weren't any results just error and leave
    if (!results)
    {
        std::cerr << "Address not usable\n";
        return false;
    }

    // If anything was found just choose the first one; if anything more
    // complicated is needed it'll be implemented later
    memcpy(&sendto_address, results->ai_addr, sizeof(sockaddr_in));

    // Set the target port
    sendto_address.sin_port = htons(port);

    freeaddrinfo(results);

    return true;
}

//====================================================================
// Clears all the data out of this socket's receive buffer
//====================================================================
void LinuxUDPSocketImpl::clearBuffer()
{
    LinuxSocketCommon::clearBuffer(
        socket_fd,
        reinterpret_cast<sockaddr*>(&peer_address),
        sizeof(sockaddr_in));
}
