#include "SignalManagerFactory.hpp"

#if defined LINUX || MACOS
#include "PosixSignalManagerImpl.hpp"
#elif defined WINDOWS
#include "NoopSignalManagerImpl.hpp"
#endif

//=============================================================================
SignalManagerImpl* SignalManagerFactory::createSignalManager()
{
#if defined LINUX || MACOS
    return new PosixSignalManagerImpl();
#else
    // Should be replaced with a proper implementation
    return new NoopSignalManagerImpl();
#endif
}
