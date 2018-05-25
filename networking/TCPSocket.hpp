// Leigh Garbs

#if !defined TCP_SOCKET_HPP
#define TCP_SOCKET_HPP

#include "Socket.hpp"

class TCPSocketImpl;

class TCPSocket : public Socket
{
  public:

    // Does nothing but call parent constructor.
    TCPSocket();

    // Does nothing.
    virtual ~TCPSocket();

    // Associates a name and port with a newly-created socket.
    bool bind(unsigned int port);

    // Instructs this socket to begin listening for incoming traffic.  Must
    // call 'bind' prior to this.
    bool listen();

    // Accepts a connection request, should one be pending.  The user can
    // specify if they want this socket to close the old socket descriptor and
    // take over the new one, or keep using the old socket descriptor and return
    // a new socket corresponding to the accepted connection.  In either case
    // a pointer to the socket handling the accepted connection is returned,
    // unless no connection was accepted, in which case 0 is returned.  Must
    // call 'listen' prior to this.
    TCPSocket* accept(bool take_over = true);

    // Connects this socket to another socket.  Used only with
    // connection-oriented protocols.
    bool connect(const std::string& hostname, unsigned int port);

    // Returns whether or not this socket is connected to another.  Connection
    // state may be improperly reported if it is entered in a disorderly fashion
    // (i.e. sudden peer disconnection without proper disconnection
    // communication).
    bool isConnected();

    // Gets the source IP address of the last received packet
    void getPeerAddress(std::string& peer_address_str) const;

  protected:

    // Sets the platform-specific socket implementation to use
    virtual void setImplementation(TCPSocketImpl* socket_impl);

  private:

    // This is a special constructor used during calls to accept.  It wraps an
    // existing platform-specific TCP socket in an instance of this class.
    explicit TCPSocket(TCPSocketImpl* socket_impl);

    // Platform-specific socket implementation to use
    TCPSocketImpl* socket_impl;
};

inline void TCPSocket::setImplementation(TCPSocketImpl* socket_impl)
{
  this->socket_impl = socket_impl;
}

#endif
