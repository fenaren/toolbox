#include <iostream>
#include <string>

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

    if (!socket_impl)
    {
        std::cerr << "Platform-specific UDP socket could not be created\n";
    }

    Socket::setImplementation(socket_impl);
}

//=============================================================================
// Destroys socket
//=============================================================================
UDPSocket::~UDPSocket()
{
    if (socket_impl)
    {
        delete socket_impl;
    }
}

//=============================================================================
// Calls implementation-specific bind
//=============================================================================
bool UDPSocket::bind(unsigned int port)
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
