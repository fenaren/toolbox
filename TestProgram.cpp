#include "TestProgram.hpp"

#include "Test.hpp"

//==============================================================================
TestProgram::TestProgram(int argc, char** argv, Test* test) :
    Program(argc, argv),
    test(test)
{
}

//==============================================================================
TestProgram::~TestProgram()
{
}

//==============================================================================
int TestProgram::run()
{
    // Maps test results to return codes
    switch(test->run())
    {
    case Test::PASSED:
        return 0;

    case Test::FAILED:
        return 1;

    case Test::SKIPPED:
        return 2;

    default:
        return -1;
    };
}

//==============================================================================
void TestProgram::processDeliveredSignals()
{
}
