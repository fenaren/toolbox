#include <iostream>

#include "FixedRateProgram.hpp"

#include "PosixTimespec.hpp"

class TestFRP : public FixedRateProgram
{
public:
    TestFRP(int argc, char** argv, const PosixTimespec& period) :
        FixedRateProgram(argc, argv, period) {};

    virtual void step() { std::cout << "Step\n"; setTerminate(true); }
};

int main(int argc, char** argv)
{
    TestFRP test_frp(argc, argv, 1.0);

    test_frp.run();

    return 0;
}
