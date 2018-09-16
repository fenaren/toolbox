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
    return Test::PASSED;
}
