#if !defined HELLO_WORLD_HPP
#define HELLO_WORLD_HPP

#include <chrono>

#include "FixedRateProgram.hpp"

class HelloWorld : public FixedRateProgram
{
public:

    HelloWorld(int                             argc,
               char**                          argv,
               const std::chrono::nanoseconds& period,
               unsigned int                    num_frames_to_execute);
    ~HelloWorld();
    virtual void step();

private:

    unsigned int num_frames_to_execute;
    unsigned int frame_counter;
};

#endif
