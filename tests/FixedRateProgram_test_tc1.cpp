#include <iostream>

#include "FixedRateProgram_test_tc1.hpp"

#include "FixedRateProgram.hpp"
#include "PosixTimespec.hpp"

//==============================================================================
FixedRateProgram_test_tc1::FixedRateProgram_test_tc1(
    int argc, char** argv, const PosixTimespec& period) :
    FixedRateProgram(argc, argv, period)
{
}

//==============================================================================
FixedRateProgram_test_tc1::~FixedRateProgram_test_tc1()
{
}

//==============================================================================
void FixedRateProgram_test_tc1::step()
{
    std::cout << "Step\n";
    setTerminate(true);
}
