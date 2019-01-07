#if !defined WINDOWS_TCP_SOCKET_IMPL_HPP
#define WINDOWS_TCP_SOCKET_IMPL_HPP

#include <winsock2.h>

#include "TCPSocketImpl.hpp"

// Defines a socket implementation specific to Windows.
class WindowsTCPSocketImpl : public TCPSocketImpl
{
public:

    // Constructs a new socket that will use the given protocol.
    WindowsTCPSocketImpl();

    // Closes the associated socket.
    virtual ~WindowsTCPSocketImpl();

    // Enables blocking on reads and writes.
    virtual bool enableBlocking();

    // Disables blocking on reads and writes.
    virtual bool disableBlocking();

    // Returns whether or not this socket blocks.
    virtual bool isBlockingEnabled();

    // Enables a timeout of the given length (in seconds) on blocking
    // operations.  A negative timeout value disables the blocking timeout. On
    // Windows, resolution is millisecond-level
    virtual void setBlockingTimeout(double blocking_timeout);

    // Returns the current blocking timeout.
    virtual double getBlockingTimeout() const;

    // Associates a name and port with a newly-created socket.  Specify 0 to
    // request any available port.  The chosen port is returned in place of the
    // argument.
    virtual bool bind(unsigned int& port);

    // Sets the socket's blocking/non-blocking state.
    virtual bool listen();

    // Accepts a connection request, should one be pending.  Used only with
    // connection-oriented protocols (like TCP).  The user can specify
    // if they want this socket to close the old socket descriptor and take
    // over the new one, or keep using the old socket descriptor and return
    // a new socket corresponding to the accepted connection.  In either case
    // a pointer to the socket handling the accepted connection is returned,
    // unless no connection was accepted, in which case 0 is returned.  Must
    // call 'listen' prior to this.
    virtual WindowsTCPSocketImpl* accept(bool take_over = true);

    // Connects this socket to another socket.  Used only with
    // connection-oriented protocols.
    virtual bool connect(const std::string& hostname, unsigned int port);

    // Returns whether or not this socket is connected to another.  Connection
    // state may be improperly reported if it is entered in a disorderly fashion
    // (i.e. sudden peer disconnection without proper disconnection
    // communication).  Does not properly report connection state before a
    // connection has been established.
    virtual bool isConnected();

    // Reads the specified amount of data from this socket into the specified
    // buffer.
    virtual int read(char* buffer, unsigned int size);

    // Writes the specified amount of data to this socket from the specified
    // buffer.
    virtual int write(const char* buffer, unsigned int size);

    // Gets the source IP address of the last received packet
    virtual void getPeerAddress(std::string& peer_address_str) const;

    // Forces this socket to discard any received data.
    virtual void clearBuffer();

private:

    // A special constructor used during accept; duplicates a socket and assumes
    // the new socket is open
    WindowsTCPSocketImpl(SOCKET       socket_fd,
                         sockaddr_in& local_address,
                         sockaddr_in& peer_address);

    // Descriptor for this socket
    SOCKET socket_fd;

    // If this socket is bound this will store the bound address
    sockaddr_in local_address;

    // The address of the socket this one is connected to
    sockaddr_in peer_address;

    // Whether or not this socket is in blocking mode
    bool is_blocking;

    // User-given blocking timeout length
    double blocking_timeout;

    // The length of blocking timeouts, in milliseconds
    INT ts_blocking_timeout;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    WindowsTCPSocketImpl(const WindowsTCPSocketImpl&);
    WindowsTCPSocketImpl& operator=(const WindowsTCPSocketImpl&);
};

inline
void WindowsTCPSocketImpl::getPeerAddress(std::string& peer_address_str) const
{
    peer_address_str = inet_ntoa(peer_address.sin_addr);
}

#endif
