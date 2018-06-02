#if !defined FIXED_RATE_PROGRAM
#define FIXED_RATE_PROGRAM

#include "Program.hpp"

#include "PosixClock.hpp"
#include "PosixTimespec.hpp"

class FixedRateProgram : public Program
{
public:

    FixedRateProgram(int argc, char** argv, double period_s);

    FixedRateProgram(int argc, char** argv, const PosixTimespec& period);

    virtual ~FixedRateProgram();

    virtual int run();

    virtual bool step() = 0;

    double getPeriod() const;

    void setPeriod(double period_s);

private:

    PosixClock    clock;
    PosixTimespec period;
};

inline double FixedRateProgram::getPeriod() const
{
    return period.getDouble();
}

inline void FixedRateProgram::setPeriod(double period_s)
{
    this->period.setDouble(period_s);
}

#endif
