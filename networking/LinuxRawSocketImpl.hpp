#if !defined LINUX_RAW_SOCKET_IMPL_HPP
#define LINUX_RAW_SOCKET_IMPL_HPP

#include <linux/if_packet.h>

#include "RawSocketImpl.hpp"

// Defines a socket implementation specific to Linux.  Raw sockets on Linux
// require root priviledges to create and use.
class LinuxRawSocketImpl : public RawSocketImpl
{
public:

    // Constructs a new Linux raw socket.
    LinuxRawSocketImpl();

    // Closes the associated socket.
    virtual ~LinuxRawSocketImpl();

    // Enables blocking on reads and writes.
    virtual bool enableBlocking();

    // Disables blocking on reads and writes.
    virtual bool disableBlocking();

    // Returns whether or not this socket blocks.
    virtual bool isBlockingEnabled();

    // Enables a timeout of the given length (seconds) on blocking operations.
    // A non-positive timeout value disables the blocking timeout.
    virtual void setBlockingTimeout(double blocking_timeout);

    // Returns the current blocking timeout (seconds)
    virtual double getBlockingTimeout() const;

    // Sets the interface from which to receive data; empty string means data
    // will be received from all available interfaces
    virtual bool setInputInterface(const std::string& interface_name);

    // Overwrites interface_name with name of current input interface; empty
    // string means data is received from all interfaces
    virtual void getInputInterface(std::string& interface_name) const;

    // Sets the interface data will be sent from
    virtual bool setOutputInterface(const std::string& interface_name);

    // Retrieves the name of the interface data will be sent from
    virtual void getOutputInterface(std::string& interface_name);

    // Reads the specified amount of data from this socket into the specified
    // buffer.
    virtual int read(unsigned char* buffer, unsigned int size);

    // Writes the specified amount of data to this socket from the specified
    // buffer.
    virtual int write(const unsigned char* buffer, unsigned int size);

    // Forces this socket to discard any received data.
    virtual void clearBuffer();

private:

    // Retrieves the number corresponding to an interface, given its name
    int getInterfaceIndex(const std::string& interface_name);

    // Descriptor for this socket
    int socket_fd;

    // Raw socket structures used during sending and receiving
    sockaddr_ll input_interface;
    sockaddr_ll output_interface;

    // Names of input and output interfaces
    std::string input_interface_name;
    std::string output_interface_name;

    double blocking_timeout;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    LinuxRawSocketImpl(const LinuxRawSocketImpl&);
    LinuxRawSocketImpl& operator=(const LinuxRawSocketImpl&);
};

inline void LinuxRawSocketImpl::setBlockingTimeout(double blocking_timeout)
{
    this->blocking_timeout = blocking_timeout;
}

inline double LinuxRawSocketImpl::getBlockingTimeout() const
{
    return this->blocking_timeout;
}

inline
void LinuxRawSocketImpl::getInputInterface(std::string& interface_name) const
{
    interface_name = input_interface_name;
}

inline void LinuxRawSocketImpl::getOutputInterface(std::string& interface_name)
{
    interface_name = output_interface_name;
}

#endif
