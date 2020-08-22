#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

#include "FixedRateProgram.hpp"

//=============================================================================================
FixedRateProgram::FixedRateProgram(int                             argc,
                                   char**                          argv,
                                   const std::chrono::nanoseconds& period,
                                   const std::chrono::nanoseconds& tolerance) :
    Program(argc, argv),
    period(period),
    tolerance(tolerance),
    completed_iterations(0L),
    terminate(false)
{
}

//=============================================================================================
FixedRateProgram::~FixedRateProgram()
{
}

//=============================================================================================
int FixedRateProgram::run()
{
    // Take the time once at the start of execution.  We'll compare to this over the course of
    // execution, rather than comparing to loop start, to determine how long to sleep after
    // each frame.  This eliminates any drift over time inherent to this code.
    std::chrono::time_point<std::chrono::steady_clock> run_start =
        std::chrono::steady_clock::now();

    while(!terminate)
    {
        // Ideally this frame starts at this time ...
        std::chrono::time_point<std::chrono::steady_clock> frame_start_ideal =
            run_start + (period * completed_iterations);

        // After the loop below this will be set to when we actually start the frame.
        std::chrono::time_point<std::chrono::steady_clock> frame_start =
            std::chrono::steady_clock::now();

        // Wait until it's time to start this frame.
        while (frame_start < frame_start_ideal - tolerance)
        {
            // This is a no-op if we're already past the ideal start time
            std::this_thread::sleep_until(frame_start_ideal);

            frame_start = std::chrono::steady_clock::now();
        }

        // Frame overruns generate an exception
        if (frame_start > frame_start_ideal + tolerance)
        {
            throw std::runtime_error("Frame overrun detected");
        }

        // Run the iterative code
        step();

        std::chrono::time_point<std::chrono::steady_clock> frame_end =
            std::chrono::steady_clock::now();

        completed_iterations++;

        // Include frame time into running frame statistics
        statistics.update(
            static_cast<std::chrono::nanoseconds>(frame_end - frame_start).count() / 1e9);
    }

    // Retrieve and print frame time used statistics
    std::string ftu_stats;
    statistics.toString(ftu_stats, "s");  // Units of seconds (s)

    std::cout << "Frame time used statistics\n" << ftu_stats;

    return 0;
}
