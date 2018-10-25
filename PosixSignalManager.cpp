#include <csignal>
#include <initializer_list>
#include <unordered_map>

#include "PosixSignalManager.hpp"

//==============================================================================
// Parses program arguments and stores in arguments
//==============================================================================
PosixSignalManager::PosixSignalManager() :
    delivery_status(std::initializer_list<int, volatile sig_atomic_t>({SIGINT, 0}))
{
}

//==============================================================================
// Nothing to do on shutdown here
//==============================================================================
PosixSignalManager::~PosixSignalManager()
{
}

//==============================================================================
// External sources can use this interface to signal this program; signals are
// not handled immediately, they are placed on a list and handled within the
// processSignals member function
//==============================================================================
void PosixSignalManager::signal(int sig)
{
    // Add this signal to our list of delivered signals
    //pthread_mutex_lock(&delivered_signals_mutex);
    //sigaddset(&delivered_signals, sig);
    //pthread_mutex_unlock(&delivered_signals_mutex);
}

//==============================================================================
// Returns a copy of the set of delivered signals
//==============================================================================
/*void PosixSignalManager::getDeliveredSignals(sigset_t& sigset)
{
    //pthread_mutex_lock(&delivered_signals_mutex);
    //sigset = this->delivered_signals;
    //pthread_mutex_unlock(&delivered_signals_mutex);
    }*/

//==============================================================================
// Returns true if sig has been delivered
//==============================================================================
bool PosixSignalManager::isSignalDelivered(int sig)
{
    //pthread_mutex_lock(&delivered_signals_mutex);
    //bool signal_delivered = sigismember(&delivered_signals, sig);
    //pthread_mutex_unlock(&delivered_signals_mutex);

    //return signal_delivered;
}

//==============================================================================
// C function "cfun" is assigned to handle signals of type sig
//==============================================================================
bool PosixSignalManager::registerSignal(int sig, void cfun(int))
{
    struct sigaction act;
    act.sa_handler = cfun;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);

    return sigaction(sig, &act, 0) != -1;
}

//==============================================================================
// Derived classes should implement this function with their signal handling
// code; get the current set of delivered signals by calling
// getDeliveredSignals() or check if a particular signal is delivered using
// isSignalDelivered(); after signals are processed use unsignal() or
// unsignalAll() to mark signals as processed
//==============================================================================
void PosixSignalManager::processDeliveredSignals()
{
    //unsignalAll();
}

//==============================================================================
// Removes a particular signal from the set of delivered signals
//==============================================================================
void PosixSignalManager::unsignal(int sig)
{
    //pthread_mutex_lock(&delivered_signals_mutex);
    //sigdelset(&delivered_signals, sig);
    //pthread_mutex_unlock(&delivered_signals_mutex);
}

//==============================================================================
// Removes all signals from the set of delivered signals
//==============================================================================
void PosixSignalManager::unsignalAll()
{
    //pthread_mutex_lock(&delivered_signals_mutex);
    //sigemptyset(&delivered_signals);
    //pthread_mutex_unlock(&delivered_signals_mutex);
}
