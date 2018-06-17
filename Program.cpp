#include <csignal>
#include <pthread.h>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

#include "Program.hpp"

//==============================================================================
// Parses program arguments and stores in arguments
//==============================================================================
Program::Program(int argc, char** argv)
{
    // Program name is always the first argument
    if (argc > 0)
    {
        name = argv[0];
    }

    // Store all arguments
    for (int i = 1; i < argc; i++)
    {
        arguments.push_back(argv[i]);
    }

    // No signals delivered, we're not even running yet
    sigemptyset(&delivered_signals);

    // Default attributes should be good enough
    pthread_mutex_init(&delivered_signals_mutex, 0);
}

//==============================================================================
// Nothing to do on shutdown here
//==============================================================================
Program::~Program()
{
    pthread_mutex_destroy(&delivered_signals_mutex);
}

//==============================================================================
// THREAD-SAFE; External sources can use this interface to signal this program;
// signals are not handled immediately, they are placed on a list and handled
// within the processSignals member function
//==============================================================================
void Program::signal(int sig)
{
    // Add this signal to our list of delivered signals
    pthread_mutex_lock(&delivered_signals_mutex);
    sigaddset(&delivered_signals, sig);
    pthread_mutex_unlock(&delivered_signals_mutex);
}

//==============================================================================
// Returns a copy of the program name
//==============================================================================
void Program::getName(std::string& name) const
{
    name = this->name;
}

//==============================================================================
// Returns a copy of the program arguments
//==============================================================================
void Program::getArguments(std::vector<std::string>& arguments) const
{
    arguments = this->arguments;
}

//==============================================================================
// THREAD-SAFE; Returns a copy of the set of delivered signals
//==============================================================================
void Program::getDeliveredSignals(sigset_t& sigset)
{
    pthread_mutex_lock(&delivered_signals_mutex);
    sigset = this->delivered_signals;
    pthread_mutex_unlock(&delivered_signals_mutex);
}

//==============================================================================
// THREAD-SAFE; Returns true if sig has been delivered
//==============================================================================
bool Program::isSignalDelivered(int sig)
{
    pthread_mutex_lock(&delivered_signals_mutex);
    bool signal_delivered = sigismember(&delivered_signals, sig);
    pthread_mutex_unlock(&delivered_signals_mutex);

    return signal_delivered;
}

//==============================================================================
// C function "cfun" is assigned to handle signals of type sig
//==============================================================================
bool Program::attachSignal(int sig, void cfun(int))
{
    struct sigaction act;
    act.sa_handler = cfun;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);

    return sigaction(SIGINT, &act, 0) != -1;
}

//==============================================================================
// Reconfigure self as a background process (daemon)
//==============================================================================
bool Program::daemonize()
{
    // Linux-specific and possibly outdated
    return daemon(0, 0) == 0;
}

//==============================================================================
// Derived classes should implement this function with their signal handling
// code; get the current set of delivered signals by calling
// getDeliveredSignals() or check if a particular signal is delivered using
// isSignalDelivered(); after signals are processed use unsignal() or
// unsignalAll() to mark signals as processed
//==============================================================================
void Program::processDeliveredSignals()
{
    unsignalAll();
}

//==============================================================================
// THREAD-SAFE; Removes a particular signal from the set of delivered signals
//==============================================================================
void Program::unsignal(int sig)
{
    pthread_mutex_lock(&delivered_signals_mutex);
    sigdelset(&delivered_signals, sig);
    pthread_mutex_unlock(&delivered_signals_mutex);
}

//==============================================================================
// THREAD-SAFE; Removes all signals from the set of delivered signals
//==============================================================================
void Program::unsignalAll()
{
    pthread_mutex_lock(&delivered_signals_mutex);
    sigemptyset(&delivered_signals);
    pthread_mutex_unlock(&delivered_signals_mutex);
}
