#include "SocketFactory.hpp"

#if defined WINDOWS
#include "WindowsRawSocketImpl.hpp"
#include "WindowsTCPSocketImpl.hpp"
#include "WindowsUDPSocketImpl.hpp"
#else
#include "PosixTCPSocketImpl.hpp"
#include "PosixUDPSocketImpl.hpp"
#if defined LINUX
#include "LinuxRawSocketImpl.hpp"
#endif // LINUX
#endif // WINDOWS

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
UDPSocketImpl* SocketFactory::createUDPSocket()
{
#if defined WINDOWS
    return new WindowsUDPSocketImpl();
#else
    return new PosixUDPSocketImpl();
#endif
}

//=============================================================================
RawSocketImpl* SocketFactory::createRawSocket()
{
#if defined WINDOWS
    return new WindowsRawSocketImpl();
#elif defined LINUX
    return new LinuxRawSocketImpl();
#else
    return 0;  // MacosRawSocketImpl not yet implemented
#endif
}

//=============================================================================
SocketFactory::SocketFactory()
{
}

//=============================================================================
SocketFactory::~SocketFactory()
{
}
