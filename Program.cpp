#include <csignal>
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
int Program::handleSignal(int sig)
{
    return 0;
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
    arguments = arguments;
}

//==============================================================================
// Reconfigure self as a background process (daemon)
//==============================================================================
bool Program::daemonize()
{
    // Linux-specific and possibly outdated
    return daemon(0, 0) == 0;
}
