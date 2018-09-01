#if !defined WINDOWS_UDP_SOCKET_IMPL_HPP
#define WINDOWS_UDP_SOCKET_IMPL_HPP

#include <WinSock2.h>
#include <stdexcept>

#include "UDPSocketImpl.hpp"

// Defines a socket implementation specific to Windows.
class WindowsUDPSocketImpl : public UDPSocketImpl
{
public:

    // Constructs a new socket that will use the given protocol.
    WindowsUDPSocketImpl() throw(std::runtime_error);

    // Closes the associated socket.
    virtual ~WindowsUDPSocketImpl();

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

    // Gets the source IP address of the last received packet
    virtual void getPeerAddress(std::string& peer_address_str) const;

    // Forces this socket to discard all received data
    virtual void clearBuffer();

private:

    // Descriptor for this socket
    SOCKET socket_fd;

    // Address bound by bind
    sockaddr_in local_address;

    // Where packets are sent with write; set with sendTo
    sockaddr_in sendto_address;

    // Source address of the last read packet
    sockaddr_in peer_address;

    // Whether or not this socket is in blocking mode
    bool is_blocking;

    // User-given blocking timeout length
    double blocking_timeout;

    // The length of blocking timeouts, in milliseconds
    INT ts_blocking_timeout;
};

inline void WindowsUDPSocketImpl::getPeerAddress(std::string& peer_address_str) const
{
    peer_address_str = inet_ntoa(peer_address.sin_addr);
}

#endif
