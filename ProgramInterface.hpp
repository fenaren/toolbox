#if !defined PROGRAM_INTERFACE_HPP
#define PROGRAM_INTERFACE_HPP

#include <string>
#include <vector>

class SignalManager;

class ProgramInterface
{
public:

    // Derived programs implement the program in here
    virtual int run() = 0;

    // Returns a copy of the program name
    virtual void getName(std::string& name) const = 0;

    // Returns a copy of the program arguments
    virtual void getArguments(std::vector<std::string>& arguments) const = 0;

protected:

    virtual SignalManager* getSignalManager() = 0;
};

#endif
