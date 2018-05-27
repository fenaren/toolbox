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

protected:

    // Arguments to the program, parsed out into switch/option and value pairs;
    // constructor fills this in
    std::vector<std::pair<std::string, std::string> > program_arguments;
};


#endif
