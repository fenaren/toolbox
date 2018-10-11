#include <ctime>
#include <iostream>

#include "FixedRateProgram_test.hpp"

#include "FixedRateProgram_test_tc1.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(FixedRateProgram_test);

//==============================================================================
FixedRateProgram_test::FixedRateProgram_test() :
    period(1.0)
{
}

//==============================================================================
FixedRateProgram_test::~FixedRateProgram_test()
{
}

//==============================================================================
Test::Result FixedRateProgram_test::run()
{
    // Normally it would not be possible for a program to receive no arguments
    FixedRateProgram_test_tc1 test_frp(0, 0, period);

    std::cout << "Period " << period << "s\n";

    // Grab start time; if we can't do that we can't test, so skip
    timespec tstart;
    SKIP_IF_TRUE(clock_gettime(CLOCK_MONOTONIC, &tstart));

    // This should run for one step that is "period" in length
    test_frp.run();

    // Grab end time; if we can't do that we can't test, so skip
    timespec tend;
    SKIP_IF_TRUE(clock_gettime(CLOCK_MONOTONIC, &tend));

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
              << "Upper bound " << period.toDouble() + epsilon << "s\n"
              << "Lower bound " << period.toDouble() - epsilon << "s\n";

    MUST_BE_TRUE(period.toDouble() + epsilon > time_taken &&
                 period.toDouble() - epsilon < time_taken);

    return Test::PASSED;
}
