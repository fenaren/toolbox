#include <ctime>
#include <iostream>

#include "FixedRateProgram.hpp"

#include "ClockImpl.hpp"

//==============================================================================
FixedRateProgram::FixedRateProgram(int argc, char** argv, double period) :
    Program(argc, argv),
    period(period),
    terminate(false)
{
}

//==============================================================================
FixedRateProgram::~FixedRateProgram()
{
}

//==============================================================================
int FixedRateProgram::run()
{
    while(!terminate)
    {
        // Used to determine the amount of time taken to execute the iterative
        // code
        frame_start = clock->getTime();

        // Run the iterative code
        step();

        // Used to determine the amount of time taken to execute the iterative
        // code
        frame_stop = clock->getTime();

        // How long was that frame
        double frame_time = frame_stop - frame_start;

        // Include frame time into running frame statistics
        statistics.update(frame_time);

        // Sleep off the rest of the frame
        clock->sleep(period - frame_time);
    }

    // Retrieve and print frame time used statistics
    std::string ftu_stats;
    statistics.toString(ftu_stats, "s");  // Units of seconds (s)

    std::cout << "Frame time used statistics\n" << ftu_stats;

    return 0;
}
