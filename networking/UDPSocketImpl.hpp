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

    // Associates a name and port with a newly-created socket.  Specify 0 to
    // request any available port.  The chosen port is returned in place of the
    // argument.
    virtual bool bind(unsigned int& port) = 0;

    // Causes outgoing messages to be sent to the specified address and port.
    virtual bool sendTo(const std::string& address, unsigned int port) = 0;

    // Gets the source IP address of the last received packet
    virtual void getPeerAddress(std::string& peer_address_str) const = 0;

private:

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    UDPSocketImpl(const UDPSocketImpl&);
    UDPSocketImpl& operator=(const UDPSocketImpl&);
};

#endif
