#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

#include "Program.hpp"

//==============================================================================
// Parses program arguments and stores in program_arguments
//==============================================================================
Program::Program(int argc, char** argv)
{
    // Program name is always the first argument
    if (argc > 0)
    {
        program_name = argv[0];
    }

    // Store all arguments
    for (int i = 1; i < argc; i++)
    {
        program_arguments.push_back(argv[i]);
    }
}

//==============================================================================
// Nothing to do on shutdown here
//==============================================================================
Program::~Program()
{
}

//==============================================================================
// Do nothing and signal success by default
//==============================================================================
int Program::signal(int sig)
{
    return 0;
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
// Returns a copy of the program name
//==============================================================================
void Program::getProgramName(std::string& name) const
{
    name = program_name;
}

//==============================================================================
// Returns a copy of the program arguments
//==============================================================================
void Program::getProgramArguments(std::vector<std::string>& arguments) const
{
    arguments = program_arguments;
}
