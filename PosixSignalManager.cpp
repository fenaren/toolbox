#include <csignal>
#include <initializer_list>
#include <stdexcept>
#include <unordered_map>

#if defined DEBUG
#include <iostream>
#endif

#include "PosixSignalManager.hpp"

//==============================================================================
// Parses program arguments and stores in arguments
//==============================================================================
PosixSignalManager::PosixSignalManager() :
    delivery_status{{SIGABRT,   0},
                    {SIGALRM,   0},
                    {SIGBUS,    0},
                    {SIGCHLD,   0},
                    {SIGCONT,   0},
                    {SIGFPE,    0},
                    {SIGHUP,    0},
                    {SIGILL,    0},
                    {SIGINT,    0},
                    {SIGKILL,   0},
                    {SIGPIPE,   0},
#if defined SIGPOLL // Not available on my macOS laptop
                    {SIGPOLL,   0},
#endif
                    {SIGPROF,   0},
                    {SIGQUIT,   0},
                    {SIGSEGV,   0},
                    {SIGSTOP,   0},
                    {SIGSYS,    0},
                    {SIGTERM,   0},
                    {SIGTRAP,   0},
                    {SIGTSTP,   0},
                    {SIGTTIN,   0},
                    {SIGTTOU,   0},
                    {SIGURG,    0},
                    {SIGUSR1,   0},
                    {SIGUSR2,   0},
                    {SIGVTALRM, 0},
                    {SIGXCPU,   0},
                    {SIGXFSZ,   0}}
{
}

//==============================================================================
// Nothing to do on shutdown here
//==============================================================================
PosixSignalManager::~PosixSignalManager()
{
}

//==============================================================================
// C function "cfun" is assigned to handle signals of type sig
//==============================================================================
bool PosixSignalManager::registerSignalHandler(int sig, void cfun(int))
{
    struct sigaction act;
    act.sa_handler = cfun;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);

    return sigaction(sig, &act, 0) != -1;
}

//==============================================================================
// External sources can use this interface to signal this program; signals are
// not handled immediately, they are placed on a list and handled within the
// processSignals member function
//==============================================================================
void PosixSignalManager::signal(int sig)
{
    try
    {
        // This is async-signal-safe, values of delivery_status are atomic
        delivery_status.at(sig) = 1;
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
bool PosixSignalManager::isSignalDelivered(int sig)
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
        sig_delivered = delivery_status.at(sig) == 1;

        // Reset the deliery flag for this signal
        delivery_status.at(sig) = 0;
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
