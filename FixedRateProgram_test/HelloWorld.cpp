#include <chrono>
#include <iostream>

#include "HelloWorld.hpp"

#include "FixedRateProgram.hpp"

//==============================================================================
HelloWorld::HelloWorld(int                             argc,
                       char**                          argv,
                       const std::chrono::nanoseconds& period,
                       unsigned int                    num_frames_to_execute) :
    FixedRateProgram(argc, argv, period),
    num_frames_to_execute(num_frames_to_execute),
    frame_counter(0)
{
}

//==============================================================================
HelloWorld::~HelloWorld()
{
}

//==============================================================================
void HelloWorld::step()
{
    std::cout << "Hello world\n";
    frame_counter++;

    if (frame_counter == num_frames_to_execute)
    {
        setTerminate(true);
    }
}
