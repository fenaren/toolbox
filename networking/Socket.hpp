#if !defined SOCKET_HPP
#define SOCKET_HPP

#include <string>

class SocketImpl;

// This is the base class for all abstract socket classes.
class Socket
{
public:

    // Closes the associated socket.
    virtual ~Socket();

    // Enables blocking on reads and writes.
    bool enableBlocking();

    // Disables blocking on reads and writes.
    bool disableBlocking();

    // Returns whether reads or writes to the socket can block or not.
    bool isBlockingEnabled();

    // Enables a timeout of the given length (in seconds) on blocking
    // operations.  A negative timeout value disables the blocking timeout.
    void setBlockingTimeout(double timeout);

    // Returns the current blocking timeout.
    double getBlockingTimeout() const;

    // Reads the specified amount of data from this socket into the specified
    // buffer.
    int read(char* buffer, unsigned int size);

    // Writes the specified amount of data to this socket from the specified
    // buffer.
    int write(const char* buffer, unsigned int size);

    // Forces this socket to discard all received data.
    void clearBuffer();

protected:

    // Constructs a new socket that will use the given protocol.  This class
    // should not be directly instantiated.
    Socket();

    // Sets the platform-specific implementation to be used
    void setImplementation(SocketImpl* socket_impl);

private:

    // A concrete socket implementation created by derived classes
    SocketImpl* socket_impl;
};

inline void Socket::setImplementation(SocketImpl* socket_impl)
{
    this->socket_impl = socket_impl;
}

#endif
