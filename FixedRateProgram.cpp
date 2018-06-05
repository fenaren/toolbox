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
    period(period_s),
    terminate(false)
{
}

//==============================================================================
//
//==============================================================================
FixedRateProgram::FixedRateProgram(
    int argc, char** argv, const PosixTimespec& tp) :
    Program(argc, argv),
    clock(CLOCK_MONOTONIC_RAW),
    period(tp),
    terminate(false)
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
    while(!terminate)
    {
        // Used to determine the amount of time taken to execute the iterative
        // code
        PosixTimespec loop_start;
        clock.getTime(loop_start);

        // Run the iterative code
        terminate = step();

        // Used to determine the amount of time taken to execute the iterative
        // code
        PosixTimespec loop_stop;
        clock.getTime(loop_stop);

        // Sleep off the rest of the frame
        clock.nanosleep(period - (loop_stop - loop_start));
    }

    return 0;
}