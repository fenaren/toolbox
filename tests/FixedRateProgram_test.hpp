#if !defined FIXED_RATE_PROGRAM_TEST_HPP
#define FIXED_RATE_PROGRAM_TEST_HPP

#include "Test.hpp"

#include "PosixTimespec.hpp"

class FixedRateProgram_test : public Test
{
public:

    FixedRateProgram_test();
    ~FixedRateProgram_test();

    // Implements the test
    virtual Test::Result run();

private:

    PosixTimespec period;
};

#endif
