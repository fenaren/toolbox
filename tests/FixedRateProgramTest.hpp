#if !defined FIXED_RATE_PROGRAM_TEST_HPP
#define FIXED_RATE_PROGRAM_TEST_HPP

#include "Test.hpp"

class FixedRateProgramTest : public Test
{
public:

    FixedRateProgramTest();
    ~FixedRateProgramTest();

    //TestFRP(int argc, char** argv, const PosixTimespec& period) :
    //    FixedRateProgram(argc, argv, period) {};

    //virtual void step() { std::cout << "Step\n"; setTerminate(true); }

    // Implements the test
    virtual Test::Result run();
};

#endif
