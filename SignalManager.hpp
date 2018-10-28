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

    // THIS FUNCTION IS ASYNC-SIGNAL-SAFE
    // Intended to be called from a signal handler for the purpose of delivering
    // a signal.  Delivery of signals is recorded in the signals map.  Use the
    // isSignalDelivered() function to query the delivery status of a particular
    // signal.
    virtual void signal(int sig);

    // Safely tests and resets the delivery status of a signal.  Delivery status
    // of the signal is returned and the delivery status itself is reset to
    // indicate that the signal is no longer delivered.
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
