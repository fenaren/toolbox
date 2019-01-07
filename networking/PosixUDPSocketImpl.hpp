#if !defined POSIX_UDP_SOCKET_IMPL_HPP
#define POSIX_UDP_SOCKET_IMPL_HPP

#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>

#include "UDPSocketImpl.hpp"

// Defines a socket implementation specific to POSIX
class PosixUDPSocketImpl : public UDPSocketImpl
{
public:

    // Constructs a new POSIX UDP socket
    PosixUDPSocketImpl();

    // Closes the associated socket.
    virtual ~PosixUDPSocketImpl();

    // Enables blocking on reads and writes.
    virtual bool enableBlocking();

    // Disable blocking on reads and writes.
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

    // Reads the specified amount of data from this socket into the specified
    // buffer.
    virtual int read(unsigned char* buffer, unsigned int size);

    // Writes the specified amount of data to this socket from the specified
    // buffer.
    virtual int write(const unsigned char* buffer, unsigned int size);

    // Causes outgoing messages to be sent to the specified address and port.
    virtual bool sendTo(const std::string& address, unsigned int port);

    // Forces this socket to discard all received data
    virtual void clearBuffer();

    // Gets the source IP address of the last received packet
    virtual void getPeerAddress(std::string& peer_address_str) const;

private:

    // Descriptor for this socket
    int socket_fd;

    // If this socket is bound with the bind function in this class, this will
    // save the bound address
    sockaddr_in local_address;

    // Where packets are sent with write; set with sendTo
    sockaddr_in sendto_address;

    // Source address of the last read packet
    sockaddr_in peer_address;

    double blocking_timeout;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    PosixUDPSocketImpl(const PosixUDPSocketImpl&);
    PosixUDPSocketImpl& operator=(const PosixUDPSocketImpl&);
};

inline void PosixUDPSocketImpl::setBlockingTimeout(double blocking_timeout)
{
    this->blocking_timeout = blocking_timeout;
}

inline double PosixUDPSocketImpl::getBlockingTimeout() const
{
    return this->blocking_timeout;
}

inline
void PosixUDPSocketImpl::getPeerAddress(std::string& peer_address_str) const
{
    peer_address_str = inet_ntoa(peer_address.sin_addr);
}

#endif
