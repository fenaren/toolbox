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

    bool getTerminate() const;

    void setTerminate(bool terminate);

private:

    PosixClock    clock;
    PosixTimespec period;

    bool terminate;
};

inline double FixedRateProgram::getPeriod() const
{
    return period.getDouble();
}

inline void FixedRateProgram::setPeriod(double period_s)
{
    this->period.setDouble(period_s);
}

inline bool FixedRateProgram::getTerminate() const
{
    return terminate;
}

inline void FixedRateProgram::setTerminate(bool terminate)
{
    this->terminate = terminate;
}

#endif
