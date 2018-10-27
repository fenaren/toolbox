#include "SignalManagerFactory.hpp"

#if defined LINUX or MACOS
#include "PosixSignalManagerImpl.hpp"
#endif

//=============================================================================
// Creates a platform-specific signal manager
//=============================================================================
SignalManagerImpl* SignalManagerFactory::createSignalManager()
{
#if defined LINUX or MACOS
    return new PosixSignalManagerImpl();
#else
    return 0;
#endif
}
