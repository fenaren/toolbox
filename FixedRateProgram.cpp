#include <time.h>

#include "FixedRateProgram.hpp"

//==============================================================================
// OnlineStatistics constructor; initializes internal state by calling reset()
//==============================================================================
FixedRateProgram::FixedRateProgram(int argc, char** argv, double period_s) :
    Program(argc, argv),
    period_s(period_s)
{
}

//==============================================================================
// OnlineStatistics constructor; initializes internal state by calling reset()
//==============================================================================
FixedRateProgram::~FixedRateProgram()
{
}

//==============================================================================
// OnlineStatistics constructor; initializes internal state by calling reset()
//==============================================================================
int FixedRateProgram::run()
{
    while(true)
    {
        // Used to determine the amount of time taken to execute the iterative
        // code
        timespec ts_begin;
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts_begin);

        // Run the iterative code
        step();

        // Used to determine the amount of time taken to execute the iterative
        // code
        timespec ts_end;
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts_end);
    }

    return 0;
}
