#if !defined FIXED_RATE_PROGRAM
#define FIXED_RATE_PROGRAM

#include "Program.hpp"

#include "PosixClock.hpp"
#include "PosixTimespec.hpp"

class FixedRateProgram : public Program
{
public:

    // Argument period_s specifies the period between iterations
    FixedRateProgram(int argc, char** argv, double period_s);

    // Argument period specifies the period between iterations
    FixedRateProgram(int argc, char** argv, const PosixTimespec& period);

    virtual ~FixedRateProgram();

    // Runs the step function every "period" length of time
    virtual int run();

    // Iterative code goes here
    virtual bool step() = 0;

    // Sets length of time between iterations in seconds
    void setPeriod(double period_s);

    // Returns length of time between iterations in seconds
    double getPeriod() const;

    // Sets length of time between iterations as a PosixTimespec
    void setPeriod(const PosixTimespec& tp);

    // Returns length of time between iterations as a PosixTimespec
    void getPeriod(PosixTimespec& tp) const;

private:

    // Time source used to compare elapsed time against period
    PosixClock clock;

    // Length of time between iterations
    PosixTimespec period;

    // Iterative loop will exit if this is true
    bool execute;
};

inline void FixedRateProgram::setPeriod(double period_s)
{
    this->period.fromDouble(period_s);
}

inline double FixedRateProgram::getPeriod() const
{
    return period.toDouble();
}

inline void FixedRateProgram::setPeriod(const PosixTimespec& tp)
{
    period = tp;
}

inline void FixedRateProgram::getPeriod(PosixTimespec& tp) const
{
    tp = period;
}

#endif
