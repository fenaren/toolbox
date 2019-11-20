#if !defined PROGRAM_INTERFACE_HPP
#define PROGRAM_INTERFACE_HPP

#include <string>
#include <vector>

class SignalManager;

// Defines the API for Programs.  See the Program header for documentation.
class ProgramInterface
{
public:

    virtual int run() = 0;

    virtual void getName(std::string& name) const = 0;

    virtual void getArguments(std::vector<std::string>& arguments) const = 0;

protected:

    virtual SignalManager* getSignalManager() = 0;
};

#endif
