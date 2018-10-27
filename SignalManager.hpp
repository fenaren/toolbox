#if !defined SIGNAL_MANAGER_HPP
#define SIGNAL_MANAGER_HPP

#include <unordered_set>

class SignalManagerImpl;

class SignalManager
{
public:

    // Nothing to do here
    SignalManager();
    virtual ~SignalManager();

    // C function "cfun" is assigned to handle signals of type sig
    virtual bool registerSignalHandler(int sig, void cfun(int));

    // External sources can use this interface to signal this program; signals
    // are not handled immediately, they are placed on a list and handled within
    // the processDeliveredSignals member function
    virtual void signal(int sig);

    // Returns true if sig has been delivered
    virtual bool isSignalDelivered(int sig);

    // Fills in a user-provided set with the list of signals we know about
    virtual void getSupportedSignals(std::unordered_set<int>& suported_signals);

private:

    SignalManagerImpl* signal_manager_impl;
};

#endif
