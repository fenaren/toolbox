#if !defined UDP_SOCKET_HPP
#define UDP_SOCKET_HPP

#include "Socket.hpp"

class UDPSocketImpl;

class UDPSocket : public Socket
{
public:

    // Does nothing but call parent constructor.
    UDPSocket();

    // Does nothing.
    virtual ~UDPSocket();

    // Associates a name and port with a newly-created socket.  Specify 0 to
    // request any available port.  The chosen port is returned in place of the
    // argument.
    bool bind(unsigned int& port);

    // Causes outgoing messages to be sent to the specified address and port.
    bool sendTo(const std::string& address, unsigned int port);

    // Gets the source IP address of the last received packet
    void getPeerAddress(std::string& peer_address_str) const;

protected:

    // Sets the platform-specific socket implementation to use
    void setImplementation(UDPSocketImpl* socket_impl);

private:

    // Platform-specific socket implementation
    UDPSocketImpl* socket_impl;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    UDPSocket(const UDPSocket&);
    UDPSocket& operator=(const UDPSocket&);
};

inline void UDPSocket::setImplementation(UDPSocketImpl* socket_impl)
{
    this->socket_impl = socket_impl;
}

#endif
