#include <iostream>
#include <signal.h>

#include "Program.hpp"

class ProgramUT : public Program
{
public:
    ProgramUT(int argc, char** argv) :
        Program(argc, argv), signal_handled(false) {}

    virtual ~ProgramUT() {}

    virtual int run()
        {
            processDeliveredSignals();

            return !signal_handled;
        }

protected:

    virtual void processDeliveredSignals()
        {
            if (isSignalDelivered(SIGINT))
            {
                signal_handled = true;
            }

            unsignalAll();
        }

private:

    bool signal_handled;
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
    program_ut.registerSignal(SIGINT, handle_signal);

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

    // run() returns 0 if successful
    int signal_ok = program_ut.run();

    return signal_ok;
}
