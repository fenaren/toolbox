#include "SignalManagerFactory.hpp"

#if defined LINUX or MACOS
#include "PosixSignalManagerImpl.hpp"
#endif

//=============================================================================
// The interface through which platform-specific signal managers are acquired.
//=============================================================================
SignalManagerImpl* SignalManagerFactory::createSignalManager()
{
#if defined LINUX or MACOS
    return new PosixSignalManagerImpl();
#else
    return 0;
#endif
}
