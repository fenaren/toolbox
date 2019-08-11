#include "SignalManagerFactory.hpp"

#if defined LINUX || MACOS
#include "PosixSignalManagerImpl.hpp"
#endif

//=============================================================================
SignalManagerImpl* SignalManagerFactory::createSignalManager()
{
#if defined LINUX || MACOS
    return new PosixSignalManagerImpl();
#else
    return 0;
#endif
}
