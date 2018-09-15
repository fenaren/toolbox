#if !defined FIXED_RATE_PROGRAM_TEST_HPP
#define FIXED_RATE_PROGRAM_TEST_HPP

#include "Test.hpp"

#include "PosixTimespec.hpp"

class FixedRateProgramTest : public Test
{
public:

    FixedRateProgramTest();
    ~FixedRateProgramTest();

    // Implements the test
    virtual Test::Result run();

private:

    PosixTimespec period;
};

#endif
