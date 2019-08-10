#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <winsock2.h>

#include "WindowsUDPSocketImpl.hpp"

#include "WindowsSocketCommon.hpp"

//=============================================================================
// Creates the socket
//=============================================================================
WindowsUDPSocketImpl::WindowsUDPSocketImpl() :
    UDPSocketImpl(),
    is_blocking(false)
{
    // Initialize the addresses to track
    memset(&local_address,  0, sizeof(sockaddr_in));
    memset(&sendto_address, 0, sizeof(sockaddr_in));
    memset(&peer_address,   0, sizeof(sockaddr_in));

    blocking_timeout = -1.0;
    ts_blocking_timeout = 0;

    // Initialize the Windows socket driver
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0)
    {
        // This socket will never work in this case
        throw std::runtime_error("WSAStartup failed");
    }

    // Create the socket descriptor
    socket_fd = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Enable broadcasting
    bool t = true;
    setsockopt(socket_fd,
               SOL_SOCKET,
               SO_BROADCAST,
               reinterpret_cast<char*>(&t),
               sizeof(bool));

    // Check for socket creation errors
    if (socket_fd == INVALID_SOCKET)
    {
        // This socket will never work in this case
        throw std::runtime_error("Cannot allocate socket");
    }
}

//=============================================================================
// Closes and destroys the socket
//=============================================================================
WindowsUDPSocketImpl::~WindowsUDPSocketImpl()
{
    WindowsSocketCommon::shutdown(socket_fd);
}

//=============================================================================
// Enables blocking
//=============================================================================
bool WindowsUDPSocketImpl::enableBlocking()
{
    return WindowsSocketCommon::enableBlocking(socket_fd, is_blocking);
}

//=============================================================================
// Disables blocking
//=============================================================================
bool WindowsUDPSocketImpl::disableBlocking()
{
    return WindowsSocketCommon::disableBlocking(socket_fd, is_blocking);
}

//=============================================================================
// Returns whether or not this socket blocks
//=============================================================================
bool WindowsUDPSocketImpl::isBlockingEnabled()
{
    return is_blocking;
}

//=============================================================================
// Sets the blocking timeout
//=============================================================================
void WindowsUDPSocketImpl::setBlockingTimeout(double blocking_timeout)
{
    WindowsSocketCommon::setBlockingTimeout(blocking_timeout,
                                            this->blocking_timeout,
                                            ts_blocking_timeout);
}

//=============================================================================
// Gets the blocking timeout
//=============================================================================
double WindowsUDPSocketImpl::getBlockingTimeout() const
{
    return blocking_timeout;
}

//=============================================================================
// Associates this socket with a name and a port
//=============================================================================
bool WindowsUDPSocketImpl::bind(unsigned int& port)
{
    return WindowsSocketCommon::bind(socket_fd,
                                     port,
                                     SOCK_DGRAM,
                                     IPPROTO_UDP,
                                     local_address);
}

//=============================================================================
// Reads data from this socket into user code
//=============================================================================
int WindowsUDPSocketImpl::read(std::uint8_t* buffer, unsigned int size)
{
    return WindowsSocketCommon::read(
        socket_fd,
        buffer,
        size,
        blocking_timeout,
        ts_blocking_timeout,
        reinterpret_cast<sockaddr*>(&peer_address),
        sizeof(sockaddr_in),
        is_blocking);
}

//=============================================================================
// Writes data from user code into this socket
//=============================================================================
int WindowsUDPSocketImpl::write(const std::uint8_t* buffer, unsigned int size)
{
    return WindowsSocketCommon::write(
        socket_fd,
        buffer,
        size,
        blocking_timeout,
        ts_blocking_timeout,
        reinterpret_cast<sockaddr*>(&sendto_address),
        sizeof(sockaddr_in),
        is_blocking);
}

//=============================================================================
// Establishes where packets from this socket will be sent
//=============================================================================
bool WindowsUDPSocketImpl::sendTo(const std::string& address,
                                  unsigned int       port)
{
    // Reset the sendto address to denote the user-specified location
    sendto_address.sin_family           = AF_INET;
    sendto_address.sin_port             = htons(port);
    sendto_address.sin_addr.S_un.S_addr = inet_addr(address.c_str());

    return true;
}

//=============================================================================
// Forces this socket to discard all received data
//=============================================================================
void WindowsUDPSocketImpl::clearBuffer()
{
    WindowsSocketCommon::clearBuffer(
        socket_fd,
        reinterpret_cast<sockaddr*>(&peer_address),
        sizeof(sockaddr_in),
        is_blocking);
}
