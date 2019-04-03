#include <ctime>
#include <iostream>
#include <string>

#include "HelloWorld.hpp"
#include "PosixTimespec.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_PROGRAM_BEGIN(FixedRateProgram_test)
TEST(TimeOneFrame)
TEST_CASES_PROGRAM_END(FixedRateProgram_test)

//==============================================================================
void FixedRateProgram_test::addTestCases()
{
    addTestCase(new TimeOneFrame());
}

//==============================================================================
Test::Result FixedRateProgram_test::TimeOneFrame::body()
{
    PosixTimespec period(1.0);

    // Normally it would not be possible for a program to receive no arguments
    HelloWorld test_frp(0, 0, period);

    std::cout << "Period " << period << "s\n";

    // Grab start time; if we can't do that we can't test, so skip
    timespec tstart;
    clock_gettime(CLOCK_MONOTONIC, &tstart);

    // This should run for one step that is "period" in length
    test_frp.run();

    // Grab end time; if we can't do that we can't test, so skip
    timespec tend;
    clock_gettime(CLOCK_MONOTONIC, &tend);

    // How much time did that take?
    tend.tv_sec -= tstart.tv_sec;
    if (tstart.tv_nsec > tend.tv_nsec)
    {
        tend.tv_sec -= 1;
        tend.tv_nsec = 1e9 - (tstart.tv_nsec - tend.tv_nsec);
    }
    else
    {
        tend.tv_nsec -= tstart.tv_nsec;
    }

    double time_taken = static_cast<double>(tend.tv_sec) +
        (static_cast<double>(tend.tv_nsec) / static_cast<double>(1e9));

    double epsilon = 0.5;
    std::cout << "Time taken " << time_taken << "s\n"
              << "Upper bound " << period + epsilon << "s\n"
              << "Lower bound " << period - epsilon << "s\n";

    MUST_BE_TRUE(period + epsilon > time_taken && period - epsilon < time_taken);

    return Test::PASSED;
}
