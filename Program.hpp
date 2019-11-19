#if !defined PROGRAM_HPP
#define PROGRAM_HPP

#include <string>
#include <utility>
#include <vector>

#include "ProgramInterface.hpp"

#include "SignalManager.hpp"

class Program : virtual public ProgramInterface
{
public:

    // Argument parsing and program initialization happens here
    Program(int argc, char** argv);

    // Nothing to do on shutdown here
    virtual ~Program();

    // Returns a copy of the program name
    virtual void getName(std::string& name) const;

    // Returns a copy of the program arguments
    virtual void getArguments(std::vector<std::string>& arguments) const;

protected:

    virtual SignalManager* getSignalManager();

private:

    // String used to launch this program at the command line
    std::string name;

    // Arguments given to the program at runtime
    std::vector<std::string> arguments;

    // Manages signals for the program
    SignalManager signal_manager;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    Program(const Program&);
    Program& operator=(const Program&);
};

//==============================================================================
inline void Program::getName(std::string& name) const
{
    name = this->name;
}

//==============================================================================
inline void Program::getArguments(std::vector<std::string>& arguments) const
{
    arguments = this->arguments;
}

//==============================================================================
inline SignalManager* Program::getSignalManager()
{
    return &signal_manager;
}

#endif
