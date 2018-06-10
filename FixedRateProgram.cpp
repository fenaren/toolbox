#include <time.h>

#include "FixedRateProgram.hpp"

#include "PosixClock.hpp"
#include "PosixTimespec.hpp"

//==============================================================================
//
//==============================================================================
FixedRateProgram::FixedRateProgram(int                  argc,
                                   char**               argv,
                                   const PosixTimespec& tp) :
    Program(argc, argv),
    clock(CLOCK_MONOTONIC_RAW),
    period(tp),
    terminate(false)
{
}

//==============================================================================
// Does nothing
//==============================================================================
FixedRateProgram::~FixedRateProgram()
{
}

//==============================================================================
// Step until we're told to stop
//==============================================================================
int FixedRateProgram::run()
{
    while(!terminate)
    {
        // Used to determine the amount of time taken to execute the iterative
        // code
        clock.getTime(frame_start);

        // Run the iterative code
        step();

        // Used to determine the amount of time taken to execute the iterative
        // code
        clock.getTime(frame_stop);

        // Sleep off the rest of the frame
        clock.nanosleep(period - (frame_stop - frame_start));
    }

    return 0;
}
