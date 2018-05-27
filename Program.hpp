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

    virtual int run() = 0;

    // Returns a copy of the program name
    void getName(std::string& name) const;

    // Returns a copy of the program arguments
    void getArguments(std::vector<std::string>& arguments) const;

protected:

    // String used to launch this program at the command line
    std::string program_name;

    // Arguments given to the program at runtime
    std::vector<std::string> program_arguments;
};


#endif
