#include <stdexcept>
#include <unordered_set>

#if defined DEBUG
#include <iostream>
#endif

#include "SignalManager.hpp"

#include "SignalManagerFactory.hpp"
#include "SignalManagerImpl.hpp"

SignalManager* signalmanager_p = 0;

// Used by the operating system to forward signals to the SignalManager,
// assuming the SignalManager is handling a signal.  Use
// SignalManager::registerSignal() to have the SignalManager start handling a
// signal.
extern "C" void handle_signal(int sig)
{
    if (signalmanager_p)
    {
        signalmanager_p->signal(sig);
    }
}

//==============================================================================
// Attempts to get a platform-specific signal manager from the signal manager
// factory.  If this works then we store the reference and use it going forward.
//==============================================================================
SignalManager::SignalManager() :
    signal_manager_impl(0)
{
    // Set the pointer used to forward signals to this SignalManager by
    // handle_signal
    signalmanager_p = this;

    signal_manager_impl = SignalManagerFactory::createSignalManager();

    if (!signal_manager_impl)
    {
        throw std::runtime_error(
            "Platform-specific signal manager could not be created");
    }
}

//==============================================================================
// Deletes the platform-specific signal manager acquired in the constructor
//==============================================================================
SignalManager::~SignalManager()
{
    delete signal_manager_impl;
}

//==============================================================================
// Registers a special signal handler for this signal which will start recording
// the signal's delivery status to internal storage.  Use isSignalDelivered() to
// retrieve the signal's current delivery status.
//==============================================================================
bool SignalManager::registerSignal(int sig)
{
    if (signal_manager_impl)
    {
        return signal_manager_impl->registerSignal(sig);
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

//==============================================================================
// Fills in a user-provided set with the list of signals we know about
//==============================================================================
void
SignalManager::getSupportedSignals(std::unordered_set<int>& supported_signals)
{
    if (signal_manager_impl)
    {
        signal_manager_impl->getSupportedSignals(supported_signals);
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
// Returns the name of the given signal
//==============================================================================
void SignalManager::getSignalName(int sig, std::string& signal_name)
{
    if (signal_manager_impl)
    {
        signal_manager_impl->getSignalName(sig, signal_name);
    }
#if defined DEBUG
    else
    {
        std::cerr <<
            "Signal handling not available on this platform, ignoring\n";
    }
#endif
}
