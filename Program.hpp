#if !defined PROGRAM_HPP
#define PROGRAM_HPP

#include <string>
#include <utility>
#include <vector>

#include "SignalManager.hpp"

class Program : public SignalManager
{
public:

    // Argument parsing and program initialization happens here
    Program(int argc, char** argv);

    // Nothing to do on shutdown here
    virtual ~Program();

    // Derived programs implement the program in here
    virtual int run() = 0;

    // Returns a copy of the program name
    void getName(std::string& name) const;

    // Returns a copy of the program arguments
    void getArguments(std::vector<std::string>& arguments) const;

    // Reconfigure self as a background process (daemon); this may be a behavior
    // that only makes sense to implement at this level on Linux systems, not
    // sure
    static bool daemonize();

protected:

    // Derived classes must implement this function with their signal handling
    // code
    virtual void processDeliveredSignals() = 0;

private:

    // String used to launch this program at the command line
    std::string name;

    // Arguments given to the program at runtime
    std::vector<std::string> arguments;
};

#endif
