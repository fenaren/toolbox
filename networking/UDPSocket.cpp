#include <stdexcept>
#include <string>

#if defined DEBUG
#include <iostream>
#endif

#include "UDPSocket.hpp"

#include "SocketFactory.hpp"

//=============================================================================
// Creates a platform-specific UDP socket
//=============================================================================
UDPSocket::UDPSocket() :
    Socket()
{
    // Get an platform-specific UDP socket
    socket_impl = SocketFactory::createUDPSocket();

    if (socket_impl)
    {
        Socket::setImplementation(socket_impl);
    }
    else
    {
        throw std::runtime_error(
            "Platform-specific UDP socket could not be created");
    }
}

//=============================================================================
// Destroys socket
//=============================================================================
UDPSocket::~UDPSocket()
{
    delete socket_impl;
}

//=============================================================================
// Calls implementation-specific bind
//=============================================================================
bool UDPSocket::bind(unsigned int& port)
{
    if (socket_impl)
    {
        return socket_impl->bind(port);
    }

    return false;
}

//=============================================================================
// Calls the implementation's sendTo
//=============================================================================
bool UDPSocket::sendTo(const std::string& address, unsigned int port)
{
    if (socket_impl)
    {
        return socket_impl->sendTo(address, port);
    }

    return false;
}

//=============================================================================
// Calls implementation-specific getLastAddress
//=============================================================================
void UDPSocket::getPeerAddress(std::string& peer_address_str) const
{
    if (socket_impl)
    {
        socket_impl->getPeerAddress(peer_address_str);
    }
}
