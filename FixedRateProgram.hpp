#if !defined FIXED_RATE_PROGRAM
#define FIXED_RATE_PROGRAM

#include "Program.hpp"

class FixedRateProgram : public Program
{
public:

    FixedRateProgram(int argc, char** argv, double period_s);

    virtual ~FixedRateProgram();

    virtual int run();

    virtual bool step() = 0;

    double getPeriod() const;

    void setPeriod(double period_s);

private:

    double period_s;
};

inline double FixedRateProgram::getPeriod() const
{
    return period_s;
}

inline void FixedRateProgram::setPeriod(double period_s)
{
    this->period_s = period_s;
}

#endif
