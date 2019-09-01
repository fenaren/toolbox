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

private:

    // String used to launch this program at the command line
    std::string name;

    // Arguments given to the program at runtime
    std::vector<std::string> arguments;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    Program(const Program&);
    Program& operator=(const Program&);
};

#endif
