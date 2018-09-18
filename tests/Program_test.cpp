#include <csignal>
#include <iostream>

#include "Program_test.hpp"

#include "Program.hpp"
#include "Program_test_tc1.hpp"
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
    Program_test test;
    TestProgram testprogram(argc, argv, &test);

    return testprogram.run();
}

//==============================================================================
Program_test::Program_test()
{
}

//==============================================================================
Program_test::~Program_test()
{
}

//==============================================================================
Test::Result Program_test::run()
{
    // Normally a Program would get a proper set of arguments
    Program_test_tc1 program_ut(0, 0);
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
