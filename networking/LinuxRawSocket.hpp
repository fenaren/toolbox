// Leigh Garbs

#if !defined LINUX_RAW_SOCKET_HPP
#define LINUX_RAW_SOCKET_HPP

#include <netpacket/packet.h>
#include <poll.h>

#include "SocketImpl.hpp"

// Defines a socket implementation specific to Linux.  Raw sockets on Linux
// require root priviledges to create and use.
class LinuxRawSocket : public SocketImpl
{
  public:

    // Constructs a new Linux socket.
    LinuxRawSocket();

    // Closes the associated socket.
    virtual ~LinuxRawSocket();

    // Enables blocking on reads and writes.
    virtual bool enableBlocking();

    // Disables blocking on reads and writes.
    virtual bool disableBlocking();

    // Returns whether or not this socket blocks.
    virtual bool isBlockingEnabled();

    // Enables a timeout of the given length (in seconds) on blocking
    // operations.  A negative timeout value disables the blocking timeout.
    virtual void setBlockingTimeout(double blocking_timeout);

    // Returns the current blocking timeout.
    virtual double getBlockingTimeout() const;

    // Sets the interface from which to receive data; empty string means data
    // will be received from all available interfaces
    virtual bool setInputInterface(const std::string& interface_name);

    // Overwrites interface_name with name of current input interface; empty
    // string means data is received from all interfaces
    virtual void getInputInterface(std::string& interface_name);

    // Sets the interface data will be sent from
    virtual bool setOutputInterface(const std::string& interface_name);

    // Retrieves the name of the interface data will be sent from
    virtual void getOutputInterface(std::string& interface_name);

    // Reads the specified amount of data from this socket into the specified
    // buffer.
    virtual int read(char* buffer, unsigned int size);

    // Writes the specified amount of data to this socket from the specified
    // buffer.
    virtual int write(const char* buffer, unsigned int size);

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

    // The blocking timeout is stored in two forms.  The first is in the double
    // form it was given in.  The second form is converted from the double form,
    // and is given directly to ppoll.
    double   blocking_timeout;
    timespec ts_blocking_timeout;
};

inline void LinuxRawSocket::getInputInterface(std::string& interface_name)
{
  interface_name = input_interface_name;
}

inline void LinuxRawSocket::getOutputInterface(std::string& interface_name)
{
  interface_name = output_interface_name;
}

#endif
