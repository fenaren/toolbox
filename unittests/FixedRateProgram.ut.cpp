#include <iostream>

#include "FixedRateProgram.hpp"

class TestFRP : public FixedRateProgram
{
public:
    TestFRP(int argc, char** argv, double period_s) :
        FixedRateProgram(argc, argv, period_s) {};

    virtual bool step() { std::cout << "Step\n"; return false;}
};

int main(int argc, char** argv)
{
    TestFRP test_frp(argc, argv, 1);

    test_frp.run();

    return 0;
}
