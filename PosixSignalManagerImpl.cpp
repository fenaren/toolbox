#include <csignal>
#include <initializer_list>
#include <stdexcept>
#include <unordered_map>

#if defined DEBUG
#include <iostream>
#endif

#include "PosixSignalManagerImpl.hpp"

std::unordered_map<int, PosixSignalManagerImpl::SignalInfo>
PosixSignalManagerImpl::signals =
{{SIGABRT,   SignalInfo("SIGABRT",   0)},
 {SIGALRM,   SignalInfo("SIGALRM",   0)},
 {SIGBUS,    SignalInfo("SIGBUS",    0)},
 {SIGCHLD,   SignalInfo("SIGCHLD",   0)},
 {SIGCONT,   SignalInfo("SIGCONT",   0)},
 {SIGFPE,    SignalInfo("SIGFPE",    0)},
 {SIGHUP,    SignalInfo("SIGHUP",    0)},
 {SIGILL,    SignalInfo("SIGILL",    0)},
 {SIGINT,    SignalInfo("SIGINT",    0)},
 {SIGKILL,   SignalInfo("SIGKILL",   0)},
 {SIGPIPE,   SignalInfo("SIGPIPE",   0)},
#if defined SIGPOLL // Not available on my macOS laptop
 {SIGPOLL,   SignalInfo("SIGPOLL",   0)},
#endif
 {SIGPROF,   SignalInfo("SIGPROF",   0)},
 {SIGQUIT,   SignalInfo("SIGQUIT",   0)},
 {SIGSEGV,   SignalInfo("SIGSEGV",   0)},
 {SIGSTOP,   SignalInfo("SIGSTOP",   0)},
 {SIGSYS,    SignalInfo("SIGSYS",    0)},
 {SIGTERM,   SignalInfo("SIGTERM",   0)},
 {SIGTRAP,   SignalInfo("SIGTRAP",   0)},
 {SIGTSTP,   SignalInfo("SIGTSTP",   0)},
 {SIGTTIN,   SignalInfo("SIGTTIN",   0)},
 {SIGTTOU,   SignalInfo("SIGTTOU",   0)},
 {SIGURG,    SignalInfo("SIGURG",    0)},
 {SIGUSR1,   SignalInfo("SIGUSR1",   0)},
 {SIGUSR2,   SignalInfo("SIGUSR2",   0)},
 {SIGVTALRM, SignalInfo("SIGVTALRM", 0)},
 {SIGXCPU,   SignalInfo("SIGXCPU",   0)},
 {SIGXFSZ,   SignalInfo("SIGXFSZ",   0)}};

//==============================================================================
// Parses program arguments and stores in arguments
//==============================================================================
PosixSignalManagerImpl::PosixSignalManagerImpl()
{
}

//==============================================================================
// Nothing to do on shutdown here
//==============================================================================
PosixSignalManagerImpl::~PosixSignalManagerImpl()
{
}

//==============================================================================
// C function "cfun" is assigned to handle signals of type sig
//==============================================================================
bool PosixSignalManagerImpl::registerSignalHandler(int sig, void cfun(int))
{
    struct sigaction act;
    act.sa_handler = cfun;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    return sigaction(sig, &act, 0) == 0;
}

//==============================================================================
// External sources can use this interface to signal this program; signals are
// not handled immediately, they are placed on a list and handled within the
// processSignals member function
//==============================================================================
void PosixSignalManagerImpl::signal(int sig)
{
    try
    {
        // This is async-signal-safe, values of delivery_status are atomic
        signals.at(sig).delivered = 1;
    }
    catch (std::out_of_range& ex)
    {
#if defined DEBUG
        std::cerr << "Unknown signal " << sig << " received, ignoring\n";
#endif
    }
}

//==============================================================================
// Returns true if sig has been delivered
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
        sig_delivered = signals.at(sig).delivered == 1;

        // Reset the deliery flag for this signal
        signals.at(sig).delivered = 0;
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
