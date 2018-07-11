#if !defined SOCKET_IMPL_HPP
#define SOCKET_IMPL_HPP

#include <string>

// This is the base class for all socket implementations.
class SocketImpl
{
public:

    // Constructs a new socket.
    SocketImpl();

    // Closes the associated socket.
    virtual ~SocketImpl();

    // Enables blocking on reads and writes.
    virtual bool enableBlocking() = 0;

    // Disables blocking on reads and writes.
    virtual bool disableBlocking() = 0;

    // Returns whether or not this socket blocks.
    virtual bool isBlockingEnabled() = 0;

    // Enables a timeout of the given length (in seconds) on blocking
    // operations.  A negative timeout value disables the blocking timeout.
    virtual void setBlockingTimeout(double timeout) = 0;

    // Returns the current blocking timeout.
    virtual double getBlockingTimeout() const = 0;

    // Reads the specified amount of data from this socket into the specified
    // buffer.
    virtual int read(char* buffer, unsigned int size) = 0;

    // Writes the specified amount of data to this socket from the specified
    // buffer.
    virtual int write(const char* buffer, unsigned int size) = 0;

    // Forces this socket to discard all received data.
    virtual void clearBuffer() = 0;
};

#endif
