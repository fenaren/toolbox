#include "SocketFactory.hpp"

#if defined WINDOWS
#include "WindowsTCPSocketImpl.hpp"
#include "WindowsUDPSocketImpl.hpp"
#else
#include "PosixTCPSocketImpl.hpp"
#include "PosixUDPSocketImpl.hpp"
#endif

//=============================================================================
// Creates a platform-specific TCP socket
//=============================================================================
TCPSocketImpl* SocketFactory::createTCPSocket()
{
#if defined WINDOWS
    return new WindowsTCPSocketImpl();
#else
    return new PosixTCPSocketImpl();
#endif
}

//=============================================================================
// Creates a platform-specific UDP socket
//=============================================================================
UDPSocketImpl* SocketFactory::createUDPSocket()
{
#if defined WINDOWS
    return new WindowsUDPSocketImpl();
#else
    return new PosixUDPSocketImpl();
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
