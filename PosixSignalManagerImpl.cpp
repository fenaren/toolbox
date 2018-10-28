#include <csignal>
#include <initializer_list>
#include <stdexcept>
#include <unordered_map>

#if defined DEBUG
#include <iostream>
#endif

#include "PosixSignalManagerImpl.hpp"

extern "C" void handle_signal(int sig);

// This initializes our static signals map with all the required POSIX signals.
// SIGPOLL isn't available on macOS so we deal with that here.  We could do
// something similar for all the signals but there's no obvious need for that
// now.
std::unordered_map<int, PosixSignalManagerImpl::SignalInfo>
PosixSignalManagerImpl::signals =
{{SIGABRT,   SignalInfo("SIGABRT",   NOT_DELIVERED)},
 {SIGALRM,   SignalInfo("SIGALRM",   NOT_DELIVERED)},
 {SIGBUS,    SignalInfo("SIGBUS",    NOT_DELIVERED)},
 {SIGCHLD,   SignalInfo("SIGCHLD",   NOT_DELIVERED)},
 {SIGCONT,   SignalInfo("SIGCONT",   NOT_DELIVERED)},
 {SIGFPE,    SignalInfo("SIGFPE",    NOT_DELIVERED)},
 {SIGHUP,    SignalInfo("SIGHUP",    NOT_DELIVERED)},
 {SIGILL,    SignalInfo("SIGILL",    NOT_DELIVERED)},
 {SIGINT,    SignalInfo("SIGINT",    NOT_DELIVERED)},
 {SIGKILL,   SignalInfo("SIGKILL",   NOT_DELIVERED)},
 {SIGPIPE,   SignalInfo("SIGPIPE",   NOT_DELIVERED)},
#if defined SIGPOLL // Not available on my macOS laptop
 {SIGPOLL,   SignalInfo("SIGPOLL",   NOT_DELIVERED)},
#endif
 {SIGPROF,   SignalInfo("SIGPROF",   NOT_DELIVERED)},
 {SIGQUIT,   SignalInfo("SIGQUIT",   NOT_DELIVERED)},
 {SIGSEGV,   SignalInfo("SIGSEGV",   NOT_DELIVERED)},
 {SIGSTOP,   SignalInfo("SIGSTOP",   NOT_DELIVERED)},
 {SIGSYS,    SignalInfo("SIGSYS",    NOT_DELIVERED)},
 {SIGTERM,   SignalInfo("SIGTERM",   NOT_DELIVERED)},
 {SIGTRAP,   SignalInfo("SIGTRAP",   NOT_DELIVERED)},
 {SIGTSTP,   SignalInfo("SIGTSTP",   NOT_DELIVERED)},
 {SIGTTIN,   SignalInfo("SIGTTIN",   NOT_DELIVERED)},
 {SIGTTOU,   SignalInfo("SIGTTOU",   NOT_DELIVERED)},
 {SIGURG,    SignalInfo("SIGURG",    NOT_DELIVERED)},
 {SIGUSR1,   SignalInfo("SIGUSR1",   NOT_DELIVERED)},
 {SIGUSR2,   SignalInfo("SIGUSR2",   NOT_DELIVERED)},
 {SIGVTALRM, SignalInfo("SIGVTALRM", NOT_DELIVERED)},
 {SIGXCPU,   SignalInfo("SIGXCPU",   NOT_DELIVERED)},
 {SIGXFSZ,   SignalInfo("SIGXFSZ",   NOT_DELIVERED)}};

//==============================================================================
PosixSignalManagerImpl::PosixSignalManagerImpl()
{
}

//==============================================================================
PosixSignalManagerImpl::~PosixSignalManagerImpl()
{
}

//==============================================================================
// Registers a special signal handler for this signal which will start recording
// the signal's delivery status to internal storage.  Use isSignalDelivered() to
// retrieve the signal's current delivery status.
//==============================================================================
bool PosixSignalManagerImpl::registerSignal(int sig)
{
    struct sigaction act;
    act.sa_handler = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    return sigaction(sig, &act, 0) == 0;
}

//==============================================================================
// THIS FUNCTION IS ASYNC-SIGNAL-SAFE
// Intended to be called from a signal handler for the purpose of delivering a
// signal.  Delivery of signals is recorded in the signals map.  Use the
// isSignalDelivered() function to query the delivery status of a particular
// signal.
//==============================================================================
void PosixSignalManagerImpl::signal(int sig)
{
    try
    {
        // at() will throw an out_of_range exception if the user gave us a
        // signal we don't recognize.  Let's not let an out_of_range exception
        // propagate out of here since we're probably running in a signal
        // handler.  I've seen strange behavior when exceptions propagate out of
        // this signal handler.
        signals.at(sig).delivery_status = DELIVERED;
    }
    catch (std::out_of_range& ex)
    {
#if defined DEBUG
        std::cerr << "Unknown signal " << sig << " received, ignoring\n";
#endif
    }
}

//==============================================================================
// Safely tests and resets the delivery status of a signal.  Delivery status of
// the signal is returned and the delivery status itself is reset to indicate
// that the signal is no longer delivered.
//==============================================================================
bool PosixSignalManagerImpl::isSignalDelivered(int sig)
{
    bool sig_delivered = false;

    bool out_of_range = false;
    std::out_of_range out_of_range_ex("");

    // Disable signals of type sig while we test and reset the current delivery
    // status of sig
    sigset_t block_sig;
    sigemptyset(&block_sig);
    sigaddset(&block_sig, sig);
    sigprocmask(SIG_BLOCK, &block_sig, 0);

    try
    {
        // This will toss an exception if sig is unknown to us.  We can't let it
        // propagate up because we have to finish our work here and reset the
        // signal mask before allowing anything else to happen.  We'll re-throw
        // any exceptions that happen here later.
        sig_delivered = signals.at(sig).delivery_status == DELIVERED;

        // Reset the deliery flag for this signal
        signals.at(sig).delivery_status = NOT_DELIVERED;
    }
    catch (std::out_of_range& ex)
    {
        out_of_range = true;
        out_of_range_ex = ex;
    }

    // Start allowing signals of type sig again
    sigprocmask(SIG_UNBLOCK, &block_sig, 0);

    // If we got an out_of_range exception earlier re-throw it
    if (out_of_range)
    {
        throw out_of_range_ex;
    }

    return sig_delivered;
}

//==============================================================================
// Fills in a user-provided set with the list of signals we know about
//==============================================================================
void PosixSignalManagerImpl::getSupportedSignals(
    std::unordered_set<int>& supported_signals)
{
    // Get rid of whatever is in there first
    supported_signals.clear();

    for (std::unordered_map<int, SignalInfo>::const_iterator i =
             signals.begin();
         i != signals.end();
         ++i)
    {
        supported_signals.insert(i->first);
    }
}
