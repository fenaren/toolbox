#if !defined POSIX_SIGNAL_MANAGER_HPP
#define POSIX_SIGNAL_MANAGER_HPP

#include <csignal>
#include <string>
#include <unordered_map>
#include <utility>

#include "SignalManagerImpl.hpp"

class PosixSignalManagerImpl : public SignalManagerImpl
{
public:

    // These do nothing
    PosixSignalManagerImpl();
    virtual ~PosixSignalManagerImpl();

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
    // indicate that the signal is no longer delivered..
    virtual bool isSignalDelivered(int sig);

    // Fills in a user-provided unordered set with the list of signals we know
    // about
    virtual
    void getSupportedSignals(std::unordered_set<int>& supported_signals);

    // Returns the name associated with the given signal
    virtual void getSignalName(int sig, std::string& signal_name);

private:

    // Used to refer to the two states assigned into the "delivery_status"
    // member of SignalInfo.  This works because both sig_atomic_t and
    // enumeration values are both some kind of integer.  We can't make the
    // "delivery_status" member this type because only accesses to sig_atomic_t
    // are guaranteed atomic.
    enum DeliveryStatus
    {
        NOT_DELIVERED,
        DELIVERED
    };

    // Stores information relevant to this class about a POSIX signal
    struct SignalInfo
    {
        SignalInfo(const std::string& name, DeliveryStatus delivery_status) :
            name(name),
            delivery_status(delivery_status)
            {
            }

        // Name of the signal (ex. "SIGINT")
        const std::string name;

        // Has the signal been delivered since the last time we checked
        volatile sig_atomic_t delivery_status;
    };

    // Maps the integer signal identifiers to a SignalInfo structure that stores
    // the delivery status of the signal as well as its name in string form (for
    // convenience).  Signal delivery status uses a volatile sig_atomic_t type
    // for async-signal-safety.
    //
    // This map can't be const because we read and write to the delivery_status
    // member of the SignalInfo struct at runtime.  As a result modifications to
    // this class must take care to NOT ADD OR REMOVE PAIRS FROM THIS MAP AFTER
    // INITIALIZATION because it is not safe for signal() to be called during
    // these operations.  Adding or removing pairs to the initialization of this
    // map in the implementation file is fine, from an async-signal-safety
    // point-of-view.
    //
    // Use the isSignalDelivered() function to query the delivery status of a
    // signal.
    static std::unordered_map<int, SignalInfo> signals;
};

inline
void PosixSignalManagerImpl::getSignalName(int sig, std::string& signal_name)
{
    signal_name = signals.at(sig).name;
}

#endif
