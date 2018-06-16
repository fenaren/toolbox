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

ProgramUT* program_utp = 0;

void handle_signal(int sig)
{
    program_utp->signal(sig);
}

int main(int argc, char** argv)
{
    ProgramUT program_ut(argc, argv);

    program_utp = &program_ut;

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

    bool success = program_ut.daemonize();
    std::cout << "THIS TEXT SHOULD NOT BE DISPLAYED\n";
    return !success;
}
