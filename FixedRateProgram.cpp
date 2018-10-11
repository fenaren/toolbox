#include <cerrno>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <system_error>

#include "FixedRateProgram.hpp"

#include "PosixClock.hpp"
#include "PosixTimespec.hpp"

//==============================================================================
// Argument "period" specifies the period between iterations
//==============================================================================
FixedRateProgram::FixedRateProgram(int                  argc,
                                   char**               argv,
                                   const PosixTimespec& period) :
    Program(argc, argv),
    clock(CLOCK_MONOTONIC),
    period(period),
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
        if (!clock.getTime(frame_start))
        {
            throw std::system_error(errno, std::system_category());
        }

        // Run the iterative code
        step();

        // Used to determine the amount of time taken to execute the iterative
        // code
        if (!clock.getTime(frame_stop))
        {
            throw std::system_error(errno, std::system_category());
        }

        // How long was that frame
        PosixTimespec frame_time = frame_stop - frame_start;

        // Include frame time into running frame statistics
        statistics.update(frame_time);

        // Sleep off the rest of the frame
        if (!clock.nanosleep(period - frame_time))
        {
            throw std::system_error(errno, std::system_category());
        }
    }

    // Retrieve and print frame time used statistics
    std::string ftu_stats;
    statistics.toString(ftu_stats, "s");  // Units of seconds (s)

    std::cout << "Frame time used statistics\n" << ftu_stats;

    return 0;
}
