#include <iostream>

#include "Program.hpp"

class ProgramUT : public Program
{
public:
    ProgramUT(int argc, char** argv) :
        Program(argc, argv) {}

    virtual ~ProgramUT() {}

    virtual int run() { return 1; }
};

int main(int argc, char** argv)
{
    ProgramUT program_ut(argc, argv);

    std::string name;
    program_ut.getProgramName(name);
    std::cout << name << "\n";

    std::vector<std::string> arguments;
    program_ut.getProgramArguments(arguments);
    for (std::vector<std::string>::const_iterator i = arguments.begin();
         i != arguments.end();
         ++i)
    {
        std::cout << *i << "\n";
    }

    program_ut.run();

    bool success = program_ut.daemonize();
    std::cout << "THIS TEXT SHOULD NOT BE DISPLAYED\n";
    return !success;
}
