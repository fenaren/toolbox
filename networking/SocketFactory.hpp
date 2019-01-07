#if !defined SOCKET_FACTORY_HPP
#define SOCKET_FACTORY_HPP

#include "RawSocketImpl.hpp"
#include "TCPSocketImpl.hpp"
#include "UDPSocketImpl.hpp"

// Provides a platform-independent way of acquiring platform-specific socket
// implementations.
class SocketFactory
{
public:

    // The interface through which platform-specific raw sockets are acquired.
    static RawSocketImpl* createRawSocket();

    // The interface through which platform-specific TCP sockets are acquired.
    static TCPSocketImpl* createTCPSocket();

    // The interface through which platform-specific UDP sockets are acquired.
    static UDPSocketImpl* createUDPSocket();

private:

    // Creating objects of this class should not be allowed.
    SocketFactory();

    // Destroying objects of this class should not be allowed.
    ~SocketFactory();

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    SocketFactory(const SocketFactory&);
    SocketFactory& operator=(const SocketFactory&);
};

#endif
