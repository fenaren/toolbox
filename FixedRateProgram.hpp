#if !defined FIXED_RATE_PROGRAM_HPP
#define FIXED_RATE_PROGRAM_HPP

#include "Program.hpp"

#include "Clock.hpp"
#include "OnlineStatistics.hpp"

class FixedRateProgram : public Program
{
public:

    // Argument "period" specifies the period between iterations
    FixedRateProgram(int argc, char** argv, double period);

    // Does nothing
    virtual ~FixedRateProgram();

    // Runs the step function every "period" length of time
    int run();

    // Iterative code goes here
    virtual void step() = 0;

    // Replace the clock in use with the given clock
    void setClock(const Clock& clock);

    void getClock(Clock& clock) const;

    // Sets length of time between iterations as a PosixTimespec
    void setPeriod(double period);

    // Returns length of time between iterations as a PosixTimespec
    double getPeriod() const;

    // Returns the last time a frame started and stopped, respectively
    double getFrameStart() const;
    double getFrameStop() const;

    // Setting to true will cause program termination before the next time
    // step() is called; a step() in progress is not interrupted
    void setTerminate(bool terminate);

    // Is the program set to terminate?
    bool getTerminate() const;

private:

    // Time source used to compare elapsed time against period
    Clock clock;

    // Length of time between iterations
    double period;

    // Updated at the beginning and ending of the frame, respectively
    double frame_start;
    double frame_stop;

    // Iterative loop will exit if this is true
    bool terminate;

    // Tracks frame time used statistics during runtime
    OnlineStatistics statistics;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    FixedRateProgram(const FixedRateProgram&);
    FixedRateProgram& operator=(const FixedRateProgram&);
};

//==============================================================================
inline void FixedRateProgram::setClock(const Clock& clock)
{
    this->clock = clock;
}

//==============================================================================
inline void FixedRateProgram::getClock(Clock& clock) const
{
    clock = this->clock;
}

//==============================================================================
inline void FixedRateProgram::setPeriod(double period)
{
    this->period = period;
}

//==============================================================================
inline double FixedRateProgram::getPeriod() const
{
    return period;
}

//==============================================================================
inline double FixedRateProgram::getFrameStart() const
{
    return frame_start;
}

//==============================================================================
inline double FixedRateProgram::getFrameStop() const
{
    return frame_stop;
}

//==============================================================================
inline void FixedRateProgram::setTerminate(bool terminate)
{
    this->terminate = terminate;
}

//==============================================================================
inline bool FixedRateProgram::getTerminate() const
{
    return terminate;
}

#endif
