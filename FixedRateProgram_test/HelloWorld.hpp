#if !defined HELLO_WORLD_HPP
#define HELLO_WORLD_HPP

#include "FixedRateProgram.hpp"

class PosixTimespec;

class HelloWorld : public FixedRateProgram
{
public:

    HelloWorld(int argc, char** argv, const PosixTimespec& period);
    ~HelloWorld();
    virtual void step();
};

#endif
