#if !defined TCP_SOCKET_IMPL_HPP
#define TCP_SOCKET_IMPL_HPP

#include "SocketImpl.hpp"

class TCPSocketImpl : public SocketImpl
{
public:

    // Does nothing but call parent constructor.
    TCPSocketImpl();

    // Does nothing.
    virtual ~TCPSocketImpl();

    // Associates a name and port with a newly-created socket.
    virtual bool bind(unsigned int port) = 0;

    // Instructs this socket to begin listening for incoming traffic.  Must call
    // 'bind' prior to this.
    virtual bool listen() = 0;

    // Accepts a connection request, should one be pending.  Used only with
    // connection-oriented protocols (like TCP).  The user can specify if they
    // want this socket to close the old socket descriptor and take over the new
    // one, or keep using the old socket descriptor and return a new socket
    // corresponding to the accepted connection.  In either case a pointer to
    // the socket handling the accepted connection is returned, unless no
    // connection was accepted, in which case 0 is returned.  Must call 'listen'
    // prior to this.
    virtual TCPSocketImpl* accept(bool take_over = true) = 0;

    // Connects this socket to another socket.  Used only with
    // connection-oriented protocols.
    virtual bool connect(const std::string& hostname, unsigned int port) = 0;

    // Returns whether or not this socket is connected to another.  Connection
    // state may be improperly reported if it is entered in a disorderly fashion
    // (i.e. sudden peer disconnection without proper disconnection
    // communication).
    virtual bool isConnected() = 0;

    // Gets the source IP address of the last received packet
    virtual void getPeerAddress(std::string& peer_address_str) const = 0;
};

#endif
