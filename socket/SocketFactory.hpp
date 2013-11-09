// Leigh Garbs

#if !defined SOCKET_FACTORY_HPP
#define SOCKET_FACTORY_HPP

#include "TCPSocketImpl.hpp"
#include "UDPSocketImpl.hpp"

// Provides a platform-independent way of acquiring platform-specific socket
// implementations.
class SocketFactory
{
  public:

    // The interface through which platform-specific TCP sockets are acquired.
    static TCPSocketImpl* createTCPSocket();

    // The interface through which platform-specific UDP sockets are acquired.
    static UDPSocketImpl* createUDPSocket();

  private:

    // Creating objects of this class should not be allowed.
    SocketFactory();

    // Destroying objects of this class should not be allowed.
    ~SocketFactory();
};

#endif
