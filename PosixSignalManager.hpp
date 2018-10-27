#if !defined POSIX_SIGNAL_MANAGER_HPP
#define POSIX_SIGNAL_MANAGER_HPP

#include <csignal>
#include <unordered_map>

#include "SignalManager.hpp"

class PosixSignalManager : public SignalManager
{
public:

    // Argument parsing and program initialization happens here
    PosixSignalManager();

    // Nothing to do on shutdown here
    virtual ~PosixSignalManager();

    // C function "cfun" is assigned to handle signals of type sig
    virtual bool registerSignalHandler(int sig, void cfun(int));

    // External sources can use this interface to signal this program; signals
    // are not handled immediately, they are placed on a list and handled within
    // the processDeliveredSignals member function
    virtual void signal(int sig);

    // Returns true if sig has been delivered
    virtual bool isSignalDelivered(int sig);

private:

    // Maintains a "delivered" status for all known signals.  Keys are POSIX
    // signals, values are a flag of type sig_atomic_t which is set to 0 when
    // the corresponding signal has not been delivered, and 1 when the
    // corresponding signal is delivered.  This map does not change size after
    // being initialized because it must be async-signal-safe at all times
    // (adding or subtracting pairs is not async-signal-safe).  As a consequence
    // of this the set of signals that are trackable by this data structure has
    // to be known at compile-time.  Calls to processDeliveredSignals() should
    // clear all the signal flags.
    std::unordered_map<int, volatile sig_atomic_t> delivery_status;
};

#endif
