// Leigh Garbs

#if !defined LINUX_UDP_SOCKET_HPP
#define LINUX_UDP_SOCKET_HPP

#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>

#include "UDPSocketImpl.hpp"

// Defines a socket implementation specific to Windows.
class LinuxUDPSocketImpl : public UDPSocketImpl
{
  public:

    // Constructs a new socket that will use the given protocol.
    LinuxUDPSocketImpl();

    // Closes the associated socket.
    virtual ~LinuxUDPSocketImpl();

    // Enables blocking on reads and writes.
    virtual bool enableBlocking();

    // Disable blocking on reads and writes.
    virtual bool disableBlocking();

    // Returns whether or not this socket blocks.
    virtual bool isBlockingEnabled();

    // Enables a timeout of the given length (in seconds) on blocking
    // operations.  A negative timeout value disables the blocking timeout.
    virtual void setBlockingTimeout(double blocking_timeout);

    // Returns the current blocking timeout.
    virtual double getBlockingTimeout() const;

    // Associates a name and port with a newly-created socket.
    virtual bool bind(unsigned int port);

    // Reads the specified amount of data from this socket into the specified
    // buffer.
    virtual int read(char* buffer, unsigned int size);

    // Writes the specified amount of data to this socket from the specified
    // buffer.
    virtual int write(const char* buffer, unsigned int size);

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

    // The blocking timeout is stored in two forms.  The first is in the double
    // form it was given in.  The second form is converted from the double form,
    // and is given directly to ppoll.
    double   blocking_timeout;
    timespec ts_blocking_timeout;
};

inline
void LinuxUDPSocketImpl::getPeerAddress(std::string& peer_address_str) const
{
  peer_address_str = inet_ntoa(peer_address.sin_addr);
}

#endif
