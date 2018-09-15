#include "FixedRateProgramTest.hpp"

#include "Test.hpp"
#include "TestFRP.hpp"
#include "TestProgram.hpp"

TEST_PROGRAM_MAIN(FixedRateProgramTest);

//==============================================================================
FixedRateProgramTest::FixedRateProgramTest() :
    period(1.0)
{
}

//==============================================================================
FixedRateProgramTest::~FixedRateProgramTest()
{
}

//==============================================================================
Test::Result FixedRateProgramTest::run()
{
    // Normally it would not be possible for a program to receive no arguments
    TestFRP test_frp(0, 0, period);
    test_frp.step();

    return Test::PASSED;
}
