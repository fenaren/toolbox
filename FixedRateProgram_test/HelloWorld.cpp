#include <iostream>

#include "HelloWorld.hpp"

#include "FixedRateProgram.hpp"
#include "PosixTimespec.hpp"

//==============================================================================
HelloWorld::HelloWorld(int argc, char** argv, const PosixTimespec& period) :
    FixedRateProgram(argc, argv, period)
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
    setTerminate(true);
}
