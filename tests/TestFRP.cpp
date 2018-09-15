#include <iostream>

#include "TestFRP.hpp"

#include "FixedRateProgram.hpp"
#include "PosixTimespec.hpp"

//==============================================================================
TestFRP::TestFRP(int argc, char** argv, const PosixTimespec& period) :
    FixedRateProgram(argc, argv, period)
{
}

//==============================================================================
TestFRP::~TestFRP()
{
}

//==============================================================================
void TestFRP::step()
{
    std::cout << "Step\n";
    setTerminate(true);
}
