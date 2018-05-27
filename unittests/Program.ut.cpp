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
    program_ut.getName(name);
    std::cout << name << "\n";

    std::vector<std::string> arguments;
    program_ut.getArguments(arguments);
    for (std::vector<std::string>::const_iterator i = arguments.begin();
         i != arguments.end();
         ++i)
    {
        std::cout << *i << "\n";
    }

    program_ut.run();

    return 0;
}
