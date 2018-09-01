#include <stdexcept>
#include <string>

#if defined DEBUG
#include <iostream>
#endif

#include "RawSocket.hpp"

#include "SocketFactory.hpp"

//==============================================================================
// Creates a platform-specific raw socket
//==============================================================================
RawSocket::RawSocket() throw(std::runtime_error) :
    Socket()
{
    // Get a platform-specific socket
    socket_impl = SocketFactory::createRawSocket();

    if (socket_impl)
    {
        Socket::setImplementation(socket_impl);
    }
    else
    {
        // This socket will never work in this case
        throw std::runtime_error(
            "Platform-specific raw socket could not be created");
    }
}

//==============================================================================
// Destroys socket
//==============================================================================
RawSocket::~RawSocket()
{
    delete socket_impl;
}

//==============================================================================
// Calls implementation-specific setInputInterface
//==============================================================================
bool RawSocket::setInputInterface(const std::string& interface_name)
{
    if (socket_impl)
    {
        return socket_impl->setInputInterface(interface_name);
    }

    return false;
}

//==============================================================================
// Calls implementation-specific getInputInterface
//==============================================================================
void RawSocket::getInputInterface(std::string& interface_name)
{
    if (socket_impl)
    {
        socket_impl->getInputInterface(interface_name);
    }
}

//==============================================================================
// Calls implementation-specific setOutputInterface
//==============================================================================
bool RawSocket::setOutputInterface(const std::string& interface_name)
{
    if (socket_impl)
    {
        return socket_impl->setOutputInterface(interface_name);
    }

    return false;
}

//==============================================================================
// Calls implementation-specific getOutputInterface
//==============================================================================
void RawSocket::getOutputInterface(std::string& interface_name)
{
    if (socket_impl)
    {
        socket_impl->getOutputInterface(interface_name);
    }
}
