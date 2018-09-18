#if !defined FIXED_RATE_PROGRAM_TEST_TC1_HPP
#define FIXED_RATE_PROGRAM_TEST_TC1_HPP

#include "FixedRateProgram.hpp"

#include "PosixTimespec.hpp"

class FixedRateProgram_test_tc1 : public FixedRateProgram
{
public:

    FixedRateProgram_test_tc1(
        int argc, char** argv, const PosixTimespec& period);

    ~FixedRateProgram_test_tc1();

    virtual void step();
};

#endif
