#if !defined POSIX_TCP_SOCKET_IMPL_HPP
#define POSIX_TCP_SOCKET_IMPL_HPP

#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdexcept>
#include <sys/socket.h>

#include "TCPSocketImpl.hpp"

// Defines a socket implementation specific to Posix.
class PosixTCPSocketImpl : public TCPSocketImpl
{
public:

    // Constructs a new Posix TCP socket.
    PosixTCPSocketImpl() throw(std::runtime_error);

    // Closes the associated socket.
    virtual ~PosixTCPSocketImpl();

    // Enables blocking on reads and writes.
    virtual bool enableBlocking();

    // Disables blocking on reads and writes.
    virtual bool disableBlocking();

    // Returns whether or not this socket blocks.
    virtual bool isBlockingEnabled();

    // Enables a timeout of the given length (seconds) on blocking operations.
    // A non-positive timeout value disables the blocking timeout.
    virtual void setBlockingTimeout(double blocking_timeout);

    // Returns the current blocking timeout (seconds).
    virtual double getBlockingTimeout() const;

    // Associates a name and port with a newly-created socket.  Specify 0 to
    // request any available port.  The chosen port is returned in place of the
    // argument.
    virtual bool bind(unsigned int& port);

    // Tells this socket to begin listening for incoming connection attempts.
    virtual bool listen();

    // Accepts a connection request, should one be pending.  The user can
    // specify if they want this socket to close the old socket descriptor and
    // take over the new one, or keep using the old socket descriptor and return
    // a new socket corresponding to the accepted connection.  In either case a
    // pointer to the socket handling the accepted connection is returned,
    // unless no connection was accepted, in which case 0 is returned.  Must
    // call 'listen' prior to this.
    virtual PosixTCPSocketImpl* accept(bool take_over = true);

    // Connects this socket to another socket.  Used only with
    // connection-oriented protocols.
    virtual bool connect(const std::string& hostname, unsigned int port);

    // Returns whether or not this socket is connected to another.  Connection
    // state may be improperly reported if it is entered in a disorderly fashion
    // (i.e. sudden peer disconnection without proper disconnection
    // communication).
    virtual bool isConnected();

    // Reads the specified amount of data from this socket into the specified
    // buffer.
    virtual int read(unsigned char* buffer, unsigned int size);

    // Writes the specified amount of data to this socket from the specified
    // buffer.
    virtual int write(const unsigned char* buffer, unsigned int size);

    // Forces this socket to discard any received data.
    virtual void clearBuffer();

    // Gets the source IP address of the last received packet
    virtual void getPeerAddress(std::string& peer_address_str) const;

private:

    // A special constructor used during accept; duplicates a socket and assumes
    // the new socket is open
    PosixTCPSocketImpl(int          socket_fd,
                       sockaddr_in& local_address,
                       sockaddr_in& peer_address,
                       double       blocking_timeout);

    // Blocks on the socket descriptor, waiting for the specified events to
    // occur, or for the timeout to be reached.  See the ppoll man page for
    // detail on the 'events' parameter.
    int doBlockingTimeout(short events);

    // Descriptor for this socket
    int socket_fd;

    // If this socket is bound this will store the bound address
    sockaddr_in local_address;

    // Address of last connected remote device
    sockaddr_in peer_address;

    double blocking_timeout;
};

inline void PosixTCPSocketImpl::setBlockingTimeout(double blocking_timeout)
{
    this->blocking_timeout = blocking_timeout;
}

inline double PosixTCPSocketImpl::getBlockingTimeout() const
{
    return this->blocking_timeout;
}

inline
void PosixTCPSocketImpl::getPeerAddress(std::string& peer_address_str) const
{
    peer_address_str = inet_ntoa(peer_address.sin_addr);
}

#endif
