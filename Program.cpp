#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

#include "Program.hpp"

//==============================================================================
Program::Program(int argc, char** argv) :
    SignalManager()
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
Program::~Program()
{
}

//==============================================================================
void Program::getName(std::string& name) const
{
    name = this->name;
}

//==============================================================================
void Program::getArguments(std::vector<std::string>& arguments) const
{
    arguments = this->arguments;
}

//==============================================================================
bool Program::daemonize()
{
    // Linux-specific and possibly outdated
    return daemon(0, 0) == 0;
}
