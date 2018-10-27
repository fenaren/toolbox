#include "SignalManagerFactory.hpp"

#if defined LINUX or MACOS
#include "PosixSignalManager.hpp"
#endif

//=============================================================================
// Creates a platform-specific signal manager
//=============================================================================
SignalManager* SignalManagerFactory::createSignalManager()
{
#if defined LINUX or MACOS
    return new PosixSignalManager();
#else
    return 0;
#endif
}
