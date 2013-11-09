// Leigh Garbs

#include "SocketFactory.hpp"

#if defined LINUX
#include "LinuxTCPSocketImpl.hpp"
#include "LinuxUDPSocketImpl.hpp"
#elif defined WINDOWS
#include "WindowsTCPSocketImpl.hpp"
#include "WindowsUDPSocketImpl.hpp"
#endif

//=============================================================================
// Creates a platform-specific TCP socket
//=============================================================================
TCPSocketImpl* SocketFactory::createTCPSocket()
{
#if defined LINUX
    return new LinuxTCPSocketImpl();
#elif defined WINDOWS
    return new WindowsTCPSocketImpl();
#else
    return 0;
#endif
}

//=============================================================================
// Creates a platform-specific UDP socket
//=============================================================================
UDPSocketImpl* SocketFactory::createUDPSocket()
{
#if defined LINUX
    return new LinuxUDPSocketImpl();
#elif defined WINDOWS
    return new WindowsUDPSocketImpl();
#else
    return 0;
#endif
}

//=============================================================================
// Does nothing
//=============================================================================
SocketFactory::SocketFactory()
{
}

//=============================================================================
// Does nothing
//=============================================================================
SocketFactory::~SocketFactory()
{
}
