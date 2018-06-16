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

    // We haven't received any signals yet
    sigemptyset(&delivered_signals);

    // Default attributes should be good enough
    pthread_mutex_init(&delivered_signals_mutex, 0);
}

//==============================================================================
// Nothing to do on shutdown here
//==============================================================================
Program::~Program()
{
}

//==============================================================================
//
//==============================================================================
bool Program::attachSignal(int sig, void cfun(int))
{
    struct sigaction act;
    act.sa_handler = cfun;
    act.sa_flags = 0;

    return sigaction(SIGINT, &act, 0) != -1;
}

//==============================================================================
//
//==============================================================================
void Program::signal(int sig)
{
    // Add this signal to our list of received signals
    pthread_mutex_lock(&delivered_signals_mutex);
    sigaddset(&delivered_signals, sig);
    pthread_mutex_unlock(&delivered_signals_mutex);
}

//==============================================================================
//
//==============================================================================
void Program::processSignals()
{
    
    pthread_mutex_lock(&delivered_signals_mutex);
    sigemptyset(&delivered_signals);
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
//
//==============================================================================
void Program::getDeliveredSignals(sigset_t& sigset)
{
    pthread_mutex_lock(&delivered_signals_mutex);
    sigset = this->delivered_signals;
    pthread_mutex_unlock(&delivered_signals_mutex);
}

//==============================================================================
// Reconfigure self as a background process (daemon)
//==============================================================================
bool Program::daemonize()
{
    // Linux-specific and possibly outdated
    return daemon(0, 0) == 0;
}
