#if !defined PROGRAM_HPP
#define PROGRAM_HPP

#include <string>
#include <utility>
#include <vector>

class Program
{
public:

    // Argument parsing and program initialization happens here
    Program(int argc, char** argv);

    // Nothing to do on shutdown here
    virtual ~Program();

    // Derived programs implement the program in here
    virtual int run() = 0;

    // External sources can use this interface to signal this program; by
    // default this does nothing
    virtual int signal(int sig);

    // Reconfigure self as a background process (daemon); this may be a behavior
    // that only makes sense to implement at this level on Linux systems, not
    // sure
    static bool daemonize();

    // Returns a copy of the program name
    void getName(std::string& name) const;

    // Returns a copy of the program arguments
    void getArguments(std::vector<std::string>& arguments) const;

private:

    // String used to launch this program at the command line
    std::string name;

    // Arguments given to the program at runtime
    std::vector<std::string> arguments;
};

#endif
