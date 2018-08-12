#if !defined RAW_SOCKET_HPP
#define RAW_SOCKET_HPP

#include <string>

#include "Socket.hpp"

class RawSocketImpl;

class RawSocket : public Socket
{
public:

    // Does nothing but call parent constructor.
    RawSocket();

    // Does nothing.
    virtual ~RawSocket();

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

protected:

    // Sets the platform-specific socket implementation to use
    void setImplementation(RawSocketImpl* socket_impl);

private:

    // Copy construction not allowed
    RawSocket(const RawSocket&);

    // Assignment not allowed
    RawSocket& operator=(const RawSocket&);

    // Platform-specific socket implementation to use
    RawSocketImpl* socket_impl;
};

inline void RawSocket::setImplementation(RawSocketImpl* socket_impl)
{
    this->socket_impl = socket_impl;
}

#endif
