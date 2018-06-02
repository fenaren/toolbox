#include <time.h>

#include "FixedRateProgram.hpp"

#include "PosixClock.hpp"
#include "PosixTimespec.hpp"

//==============================================================================
//
//==============================================================================
FixedRateProgram::FixedRateProgram(int argc, char** argv, double period_s) :
    Program(argc, argv),
    clock(CLOCK_MONOTONIC_RAW),
    period(period_s)
{
}

//==============================================================================
//
//==============================================================================
FixedRateProgram::FixedRateProgram(
    int argc, char** argv, const PosixTimespec& tp) :
    Program(argc, argv),
    clock(CLOCK_MONOTONIC_RAW),
    period(tp)
{
}

//==============================================================================
//
//==============================================================================
FixedRateProgram::~FixedRateProgram()
{
}

//==============================================================================
//
//==============================================================================
int FixedRateProgram::run()
{
    while(true)
    {
        // Used to determine the amount of time taken to execute the iterative
        // code
        PosixTimespec loop_start;
        clock.getTime(loop_start);

        // Run the iterative code
        step();

        // Used to determine the amount of time taken to execute the iterative
        // code
        PosixTimespec loop_stop;
        clock.getTime(loop_stop);

        // Sleep until the end of the frame
    }

    return 0;
}
