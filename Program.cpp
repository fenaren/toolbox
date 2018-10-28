#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

#include "Program.hpp"

Program* program_p = 0;

// Used by the operating system to deliver signals to Programs, assuming
// handle_signals has been assigned to a signal.  Does nothing but forward the
// signal to a SignalManager where it can be dealt with appropriately.  Programs
// are SignalManagers so we can signal the Program directly here.
extern "C" void handle_signal(int sig)
{
    if (program_p)
    {
        program_p->signal(sig);
    }
}

//==============================================================================
// Parses program arguments and stores in arguments
//==============================================================================
Program::Program(int argc, char** argv) :
    SignalManager()
{
    // Set the global pointer used to forward signals to this program
    program_p = this;

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
}

//==============================================================================
// Nothing to do on shutdown here
//==============================================================================
Program::~Program()
{
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
// Reconfigure self as a background process (daemon)
//==============================================================================
bool Program::daemonize()
{
    // Linux-specific and possibly outdated
    return daemon(0, 0) == 0;
}
