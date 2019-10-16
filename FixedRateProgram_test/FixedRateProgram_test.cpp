#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>

#include "FixedRateProgram_test.hpp"

#include "HelloWorld.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(FixedRateProgram_test);

//==============================================================================
void FixedRateProgram_test::addTestCases()
{
    ADD_TEST_CASE(Run);
}

//==============================================================================
Test::Result FixedRateProgram_test::Run::body()
{
#if defined MACOS || LINUX
    std::chrono::nanoseconds period(static_cast<std::uint32_t>(5e8));
    double period_sec = period.count() / 1e9;

    unsigned int iterations = 6;

    // Normally it would not be possible for a program to receive no arguments
    HelloWorld test_frp(0, 0, period, 6);

    std::cout << "Period " << period_sec << "s\n";

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

    double epsilon = 0.25;
    double time_taken_ideal = period_sec * (iterations - 1);

    double time_taken_upperbound = time_taken_ideal + epsilon;
    double time_taken_lowerbound = time_taken_ideal - epsilon;

    std::cout << "Time taken " << time_taken << "s\n"
              << "Upper bound " << time_taken_upperbound << "s\n"
              << "Lower bound " << time_taken_lowerbound << "s\n";

    MUST_BE_TRUE(time_taken <= time_taken_upperbound &&
                 time_taken >= time_taken_lowerbound);

    return Test::PASSED;
#else
    return Test::SKIPPED;
#endif
}
