#if !defined SIGNAL_MANAGER_IMPL_HPP
#define SIGNAL_MANAGER_IMPL_HPP

#include <string>
#include <unordered_set>

class SignalManagerImpl
{
public:

    // These do nothing
    SignalManagerImpl();
    virtual ~SignalManagerImpl();

    // Registers a special signal handler for this signal which will start
    // recording the signal's delivery status to internal storage.  Use
    // isSignalDelivered() to retrieve the signal's current delivery status.
    virtual bool registerSignal(int sig) = 0;

    // THIS FUNCTION IS ASYNC-SIGNAL-SAFE
    // Intended to be called from a signal handler for the purpose of delivering
    // a signal.  Delivery of signals is recorded in the signals map.  Use the
    // isSignalDelivered() function to query the delivery status of a particular
    // signal.
    virtual void signal(int sig) = 0;

    // Safely tests and resets the delivery status of a signal.  Delivery status
    // of the signal is returned and the delivery status itself is reset to
    // indicate that the signal is no longer delivered.
    virtual bool isSignalDelivered(int sig) = 0;

    // Fills in a user-provided set with the list of signals we know about
    virtual
    void getSupportedSignals(std::unordered_set<int>& supported_signals) = 0;

    // Returns the name associated with the given signal
    virtual void getSignalName(int sig, std::string& signal_name) = 0;
};

#endif
