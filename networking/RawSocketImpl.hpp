#if !defined RAW_SOCKET_IMPL_HPP
#define RAW_SOCKET_IMPL_HPP

#include "SocketImpl.hpp"

class RawSocketImpl : public SocketImpl
{
public:

    // Does nothing but call parent constructor.
    RawSocketImpl();

    // Does nothing.
    virtual ~RawSocketImpl();

    // Sets the interface from which to receive data; empty string means data
    // will be received from all available interfaces
    virtual bool setInputInterface(const std::string& interface_name) = 0;

    // Overwrites interface_name with name of current input interface; empty
    // string means data is received from all interfaces
    virtual void getInputInterface(std::string& interface_name) = 0;

    // Sets the interface data will be sent from
    virtual bool setOutputInterface(const std::string& interface_name) = 0;

    // Retrieves the name of the interface data will be sent from
    virtual void getOutputInterface(std::string& interface_name) = 0;
};

#endif
