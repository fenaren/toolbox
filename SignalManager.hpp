#if !defined SIGNAL_MANAGER_HPP
#define SIGNAL_MANAGER_HPP

#include <unordered_set>

class SignalManagerImpl;

class SignalManager
{
public:

    // Attempts to get a platform-specific signal manager from the signal
    // manager factory.  If this works then we store the reference and use it
    // going forward.
    SignalManager();

    // Deletes the platform-specific signal manager acquired in the constructor
    virtual ~SignalManager();

    // Registers a special signal handler for this signal which will start
    // recording the signal's delivery status to internal storage.  Use
    // isSignalDelivered() to retrieve the signal's current delivery status.
    virtual bool registerSignal(int sig);

    // External sources can use this interface to signal this program; signals
    // are not handled immediately, they are placed on a list and handled within
    // the processDeliveredSignals member function
    virtual void signal(int sig);

    // Returns true if sig has been delivered
    virtual bool isSignalDelivered(int sig);

    // Fills in a user-provided set with the list of signals we know about
    virtual
    void getSupportedSignals(std::unordered_set<int>& supported_signals);

    // Returns the name of the given signal
    virtual void getSignalName(int sig, std::string& signal_name);

private:

    SignalManagerImpl* signal_manager_impl;
};

#endif
