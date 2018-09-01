#include <cstdio>
#include <errno.h>
#include <cstring>
#include <fcntl.h>
#include <netdb.h>
#include <poll.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#if defined DEBUG
#include <iostream>
#endif

#include "PosixTCPSocketImpl.hpp"

#include "PosixSocketCommon.hpp"

//==============================================================================
// Creates a Posix TCP socket
//==============================================================================
PosixTCPSocketImpl::PosixTCPSocketImpl() throw(std::runtime_error) :
    blocking_timeout(0.0)
{
    // Create the socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1)
    {
        throw std::runtime_error(strerror(errno));
    }
}

//==============================================================================
// Special constructor that encapsulates an already-created TCP socket
//==============================================================================
PosixTCPSocketImpl::PosixTCPSocketImpl(int          socket_fd,
                                       sockaddr_in& local_address,
                                       sockaddr_in& peer_address,
                                       double       blocking_timeout) :
    socket_fd(socket_fd),
    local_address(local_address),
    peer_address(peer_address),
    blocking_timeout(blocking_timeout)
{
}

//==============================================================================
// Shuts this socket down
//==============================================================================
PosixTCPSocketImpl::~PosixTCPSocketImpl()
{
    PosixSocketCommon::shutdown(socket_fd);
}

//==============================================================================
// Enables blocking
//==============================================================================
bool PosixTCPSocketImpl::enableBlocking()
{
    return PosixSocketCommon::enableBlocking(socket_fd);
}

//==============================================================================
// Disable blocking
//==============================================================================
bool PosixTCPSocketImpl::disableBlocking()
{
    return PosixSocketCommon::disableBlocking(socket_fd);
}

//==============================================================================
// Returns blocking status
//==============================================================================
bool PosixTCPSocketImpl::isBlockingEnabled()
{
    return PosixSocketCommon::isBlockingEnabled(socket_fd);
}

//==============================================================================
// Binds this socket to a local address
//==============================================================================
bool PosixTCPSocketImpl::bind(unsigned int& port)
{
    return PosixSocketCommon::bind(socket_fd, local_address, port);
}

//==============================================================================
// Flags this socket as one that will listen
//==============================================================================
bool PosixTCPSocketImpl::listen()
{
    // Start listening on this socket
    if (::listen(socket_fd, 0) == -1)
    {
#if defined DEBUG
        perror("PosixTCPSocketImpl::listen");
#endif
        return false;
    }

    return true;
}

//==============================================================================
// Looks for any incoming connections
//==============================================================================
PosixTCPSocketImpl* PosixTCPSocketImpl::accept(bool take_over)
{
    // Is a valid timeout set?
    if (isBlockingEnabled() && blocking_timeout > 0.0)
    {
        // Perform the blocking timeout and check if the POLLIN event occurred
        if (PosixSocketCommon::doBlockingTimeout(
                socket_fd, POLLIN, blocking_timeout) == 0)
        {
            // Accepting now will block, but we've blocked long enough already,
            // so return instead and let the user try again if they want
            return 0;
        }
    }

    // Will hold length of returned sockaddr
    socklen_t addrlen = sizeof(sockaddr_in);

    // Look for an incoming connection
    int new_socket_fd =
        ::accept(socket_fd, (sockaddr*)&peer_address, &addrlen);

    // Check for errors
    if (new_socket_fd == -1)
    {
#if defined DEBUG
        if (errno != EAGAIN && errno != EWOULDBLOCK)
        {
            perror("PosixTCPSocketImpl::accept");
        }
#endif
        // A failure here seems like it wouldn't necessarily mean objects of
        // this class become unusable, but I could be wrong
        return 0;
    }

    // A connection was detected, deal with it
    if (take_over)
    {
        // Copy the old file descriptor status
        int status = fcntl(socket_fd, F_GETFL);
        if (status != -1)
        {
            if (fcntl(new_socket_fd, F_SETFL, status) == -1)
            {
#if defined DEBUG
                perror("PosixTCPSocketImpl::accept");
#endif
            }
        }
#if defined DEBUG
        else
        {
            perror("PosixTCPSocketImpl::accept");
        }
#endif

        // Start using the new descriptor
        PosixSocketCommon::shutdown(socket_fd);
        socket_fd = new_socket_fd;

        return this;
    }

    // Make a new socket and return it; the user is responsible for getting rid
    // of it
    return new PosixTCPSocketImpl(new_socket_fd,
                                  local_address,
                                  peer_address,
                                  blocking_timeout);
}

//==============================================================================
// Attempts a connection to a remote device
//==============================================================================
bool PosixTCPSocketImpl::connect(const std::string& hostname,
                                 unsigned int       port)
{
    // Create some hints for getaddrinfo
    addrinfo hints = { 0 };
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags    = 0;

    // Will point to the results list
    addrinfo* results = 0;

    // Look up the provided hostname
    int ret = getaddrinfo(hostname.c_str(), 0, &hints, &results);

    // If there weren't any results just error and leave
    if (!results)
    {
#if defined DEBUG
        std::cerr << "PosixTCPSocketImpl::connect: " << gai_strerror(ret)
                  << "\n";
#endif
        return false;
    }

    // If anything was found just choose the first one; if anything more
    // complicated is needed it'll be implemented later

#if defined DEBUG
    // Warn if we got more than one return
    if (results->ai_next)
    {
        std::cerr << "PosixTCPSocketImpl::connect: Multiple addrinfo results "
                  << "returned, arbitrarily choosing the first one\n";
    }
#endif
    memcpy(&peer_address, results->ai_addr, sizeof(sockaddr_in));
    peer_address.sin_port = htons(port);

    // Do the connect
    ret = ::connect(socket_fd,
                    reinterpret_cast<sockaddr*>(&peer_address),
                    sizeof(sockaddr_in));

    // Release addrinfo memory back to the kernel; freeaddrinfo returns nothing
    // so no need to check for errors here
    freeaddrinfo(results);

    // Check for errors from the connect earlier
    if (ret == -1)
    {
#if defined DEBUG
        perror("PosixTCPSocketImpl::connect");
#endif
        return false;
    }

    return true;
}

//==============================================================================
// Returns whether or not this socket is connected to another
//==============================================================================
bool PosixTCPSocketImpl::isConnected()
{
    // See what happens if we look at a single byte but don't remove it from the
    // buffer
    char buf;
    int ret = recv(socket_fd, &buf, 1, MSG_PEEK | MSG_DONTWAIT);

    // If the previous read returned 0, the peer performed an orderly shutdown
    // and the socket is therefore not connected.  Besides that case, if the
    // read results in an ENOTCONN error, this also obviously means the socket
    // is not connected.  Consider the socket connected in any other case.
    return !(ret == 0 || (ret == -1 && errno == ENOTCONN));
}

//==============================================================================
// Reads data from socket into buffer
//==============================================================================
int PosixTCPSocketImpl::read(unsigned char* buffer, unsigned int size)
{
    return PosixSocketCommon::read(
        socket_fd, buffer, size, blocking_timeout, 0, 0);
}

//==============================================================================
// Writes data to socket
//==============================================================================
int PosixTCPSocketImpl::write(const unsigned char* buffer, unsigned int size)
{
    return PosixSocketCommon::write(
        socket_fd, buffer, size, blocking_timeout, 0, 0);
}

//==============================================================================
// Clears socket of any received data
//==============================================================================
void PosixTCPSocketImpl::clearBuffer()
{
    PosixSocketCommon::clearBuffer(socket_fd, 0, 0);
}
