// Leigh Garbs

#if !defined UDP_SOCKET_IMPL_HPP
#define UDP_SOCKET_IMPL_HPP

#include "SocketImpl.hpp"

class UDPSocketImpl : public SocketImpl
{
  public:

    // Does nothing but call parent constructor.
    UDPSocketImpl();

    // Does nothing.
    virtual ~UDPSocketImpl();

    // Associates a name and port with a newly-created socket.
    virtual bool bind(unsigned int port) = 0;

    // Causes outgoing messages to be sent to the specified address and port.
    virtual bool sendTo(const std::string& address, unsigned int port) = 0;

    // Gets the source IP address of the last received packet
    virtual void getPeerAddress(std::string& peer_address_str) const = 0;
};

#endif
