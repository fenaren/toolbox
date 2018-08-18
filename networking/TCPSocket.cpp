#include <stdexcept>
#include <string>

#if defined DEBUG
#include <iostream>
#endif

#include "TCPSocket.hpp"

#include "SocketFactory.hpp"

//=============================================================================
// Creates a platform-specific TCP socket
//=============================================================================
TCPSocket::TCPSocket() :
    Socket()
{
    // Get a platform-specific socket
    socket_impl = SocketFactory::createTCPSocket();

    if (socket_impl)
    {
        Socket::setImplementation(socket_impl);
    }
    else
    {
        throw std::runtime_error(
            "Platform-specific TCP socket could not be created");
    }
}

//=============================================================================
// Special constructor used during accept; creates a TCPSocket for an
// already-created implementation-specific TCP socket
//=============================================================================
TCPSocket::TCPSocket(TCPSocketImpl* socket_impl) :
    Socket(),
    socket_impl(socket_impl)
{
    Socket::setImplementation(socket_impl);
}

//=============================================================================
// Destroys socket
//=============================================================================
TCPSocket::~TCPSocket()
{
    delete socket_impl;
}

//=============================================================================
// Calls implementation-specific bind
//=============================================================================
bool TCPSocket::bind(unsigned int& port)
{
    if (socket_impl)
    {
        return socket_impl->bind(port);
    }

    return false;
}

//=============================================================================
// Calls the implementation-specific listen
//=============================================================================
bool TCPSocket::listen()
{
    if (socket_impl)
    {
        return socket_impl->listen();
    }

    return false;
}

//=============================================================================
// Calls the implementation-specific accept
//=============================================================================
TCPSocket* TCPSocket::accept(bool take_over)
{
    if (socket_impl)
    {
        TCPSocketImpl* new_socket_impl = socket_impl->accept(take_over);

        if (!new_socket_impl)
        {
            return 0;
        }
        else if (new_socket_impl != socket_impl)
        {
            return new TCPSocket(new_socket_impl);
        }
        else
        {
            return this;
        }
    }

    return 0;
}

//=============================================================================
// Calls the implementation-specific connect
//=============================================================================
bool TCPSocket::connect(const std::string& hostname, unsigned int port)
{
    if (socket_impl)
    {
        return socket_impl->connect(hostname, port);
    }

    return false;
}

//=============================================================================
// Calls the implementation-specific isConnected
//=============================================================================
bool TCPSocket::isConnected()
{
    if (socket_impl)
    {
        return socket_impl->isConnected();
    }

    return false;
}

//=============================================================================
// Calls implementation-specific getLastAddress
//=============================================================================
void TCPSocket::getPeerAddress(std::string& peer_address_str) const
{
    if (socket_impl)
    {
        socket_impl->getPeerAddress(peer_address_str);
    }
}
