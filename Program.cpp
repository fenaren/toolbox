#include "Program.hpp"

#include "SignalManager.hpp"

SignalManager Program::signal_manager;

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
Program::~Program()
{
}
