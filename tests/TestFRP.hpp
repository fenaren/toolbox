#if !defined TEST_FRP_HPP
#define TEST_FRP_HPP

#include "FixedRateProgram.hpp"

#include "PosixTimespec.hpp"

class TestFRP : public FixedRateProgram
{
public:

    TestFRP(int argc, char** argv, const PosixTimespec& period);
    ~TestFRP();

    virtual void step();
};

#endif
