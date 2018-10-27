#if defined DEBUG
#include <iostream>
#endif

#include "SignalManager.hpp"

#include "SignalManagerFactory.hpp"

//==============================================================================
SignalManager::SignalManager() :
    signal_manager_impl(0)
{
}

//==============================================================================
SignalManager::~SignalManager()
{
}

//==============================================================================
// C function "cfun" is assigned to handle signals of type sig
//==============================================================================
bool SignalManager::registerSignalHandler(int sig, void cfun(int))
{
    if (signal_manager_impl)
    {
        return signal_manager_impl->registerSignalHandler(sig, cfun);
    }

#if defined DEBUG
    std::cerr << "Signal handling not available on this platform, ignoring\n";
#endif

    return false;
}

//==============================================================================
// External sources can use this interface to signal this program; signals are
// not handled immediately, they are placed on a list and handled within the
// processDeliveredSignals member function
//==============================================================================
void SignalManager::signal(int sig)
{
    if (signal_manager_impl)
    {
        signal_manager_impl->signal(sig);
    }
#if defined DEBUG
    else
    {
        std::cerr <<
            "Signal handling not available on this platform, ignoring\n";
    }
#endif
}

//==============================================================================
// Returns true if sig has been delivered
//==============================================================================
bool SignalManager::isSignalDelivered(int sig)
{
    if (signal_manager_impl)
    {
        return signal_manager_impl->isSignalDelivered(sig);
    }

#if defined DEBUG
    std::cerr << "Signal handling not available on this platform, ignoring\n";
#endif

    return false;
}
