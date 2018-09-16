#include "ProgramTest.hpp"

#include "Program.hpp"
#include "Test.hpp"
#include "TestProgramMain.hpp"

TEST_PROGRAM_MAIN(ProgramTest);

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
/*    ProgramUT program_ut(argc, argv);
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
*/
    return Test::PASSED;
}
