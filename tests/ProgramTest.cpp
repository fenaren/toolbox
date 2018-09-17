#include <csignal>
#include <iostream>

#include "ProgramTest.hpp"

#include "Program.hpp"
#include "ProgramUT.hpp"
#include "Test.hpp"
#include "TestProgram.hpp"

// Can't use the TEST_PROGRAM_MAIN macro here, need a special main to test
// signal handling

Program* program_p = 0;

extern "C" void handle_signal(int sig)
{
    if (program_p)
    {
        program_p->signal(sig);
    }
}

int main(int argc, char** argv)
{
    ProgramTest test;
    TestProgram testprogram(argc, argv, &test);

    return testprogram.run();
}

//==============================================================================
ProgramTest::ProgramTest()
{
}

//==============================================================================
ProgramTest::~ProgramTest()
{
}

//==============================================================================
Test::Result ProgramTest::run()
{
    // Normally a Program would get a proper set of arguments
    ProgramUT program_ut(0, 0);
    program_p = &program_ut;

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
    //raise(SIGCONT);

    // Returns 0 if successful
    if (program_ut.run() == 0)
    {
        return Test::PASSED;
    }

    return Test::FAILED;
}
