#include "SignalManagerFactory.hpp"

#if defined LINUX
#include "PosixSignalManagerImpl.hpp"
#elif defined MACOS
#include "PosixSignalManagerImpl.hpp"
#endif

//=============================================================================
SignalManagerImpl* SignalManagerFactory::createSignalManager()
{
#if defined LINUX
    return new PosixSignalManagerImpl();
#elif defined MACOS
    return new PosixSignalManagerImpl();
#else
    return 0;
#endif
}
