#include <iostream>
#include <signal.h>

#include "Program.hpp"

class ProgramUT : public Program
{
public:
    ProgramUT(int argc, char** argv) :
        Program(argc, argv) {}

    virtual ~ProgramUT() {}

    virtual int run()
        {
            processDeliveredSignals();
            processDeliveredSignals();
            return 1;
        }

protected:

    virtual void processDeliveredSignals()
        {
            if (isSignalDelivered(SIGINT))
            {
                std::cout << "SIGINT received\n";
            }

            unsignalAll();
        }
};

ProgramUT* program_utp = 0;

extern "C" void handle_signal(int sig)
{
    if (program_utp)
    {
        program_utp->signal(sig);
    }
}

int main(int argc, char** argv)
{
    ProgramUT program_ut(argc, argv);
    program_utp = &program_ut;

    // This has to happen after the assignment above because handle_signal
    // dereferences program_utp
    program_ut.attachSignal(SIGINT, handle_signal);

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

    // Raise some signals to test Program signal handling
    raise(SIGINT);
    raise(SIGCONT);

    program_ut.run();

    bool success = program_ut.daemonize();
    std::cout << "THIS TEXT SHOULD NOT BE DISPLAYED\n";
    return !success;
}
