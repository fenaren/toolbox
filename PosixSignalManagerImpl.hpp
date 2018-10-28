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

    // Argument parsing and program initialization happens here
    PosixSignalManagerImpl();

    // Nothing to do on shutdown here
    virtual ~PosixSignalManagerImpl();

    // C function "cfun" is assigned to handle signals of type sig
    virtual bool registerSignalHandler(int sig, void cfun(int));

    // External sources can use this interface to signal this program; signals
    // are not handled immediately, they are placed on a list and handled within
    // the processDeliveredSignals member function
    virtual void signal(int sig);

    // Returns true if sig has been delivered
    virtual bool isSignalDelivered(int sig);

    // Fills in a user-provided set with the list of signals we know about
    virtual
    void getSupportedSignals(std::unordered_set<int>& supported_signals);

    virtual void getSignalName(int sig, std::string& signal_name);

private:

    // Stores information relevant to this class about a POSIX signal
    struct SignalInfo
    {
        SignalInfo(const std::string& name, sig_atomic_t delivered) :
            name(name),
            delivered(delivered)
            {
            }

        // Name of the signal (ex. "SIGINT")
        const std::string name;

        // Has the signal been delivered since the last time we checked
        volatile sig_atomic_t delivered;
    };

    // Maintains a "delivered" status for all known signals.  Keys are POSIX
    // signals, values are a flag of type sig_atomic_t which is set to 0 when
    // the corresponding signal has not been delivered, and 1 when the
    // corresponding signal is delivered.  This map does not change size after
    // being initialized because it must be async-signal-safe at all times
    // (adding or subtracting pairs is not async-signal-safe).  As a consequence
    // of this the set of signals that are trackable by this data structure has
    // to be known at compile-time.
    static std::unordered_map<int, SignalInfo> signals;
};

inline
void PosixSignalManagerImpl::getSignalName(int sig, std::string& signal_name)
{
    signal_name = signals.at(sig).name;
}

#endif
