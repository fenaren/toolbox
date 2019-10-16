#if !defined FIXED_RATE_PROGRAM_HPP
#define FIXED_RATE_PROGRAM_HPP

#include <chrono>

#include "Program.hpp"

#include "OnlineStatistics.hpp"

class FixedRateProgram : public Program
{
public:

    // Arguments "argc" and "argv" are needed by Program.  Arguments "period"
    // and "tolerance" are new here.  The "period" argument specifies the fixed
    // rate at which this program should execute.  The "tolerance" argument
    // specifies how close we have to be to the ideal start time to be
    // considered at the start time.  By default this is set to a
    // human-noticeable 100 milliseconds.
    FixedRateProgram(int                             argc,
                     char**                          argv,
                     const std::chrono::nanoseconds& period,
                     const std::chrono::nanoseconds& tolerance =
                     std::chrono::nanoseconds(static_cast<unsigned int>(1e8)));

    // Does nothing
    virtual ~FixedRateProgram();

    // Runs the step function every "period" length of time
    int run();

    // Iterative code goes here
    virtual void step() = 0;

    // Sets length of time between step() executions
    void setPeriod(const std::chrono::nanoseconds& period);

    // Returns length of time between step() executions
    void getPeriod(std::chrono::nanoseconds& period) const;

    // Sets allowable error between the ideal frame start time and the actual
    // frame start time
    void setTolerance(const std::chrono::nanoseconds& tolerance);

    // Returns the allowable error between the ideal frame start time and actual
    // frame start time
    void getTolerance(std::chrono::nanoseconds& tolerance) const;

    // Setting to true will cause program termination before the next time
    // step() is called; a step() in progress is not interrupted
    void setTerminate(bool terminate);

    // Is the program set to terminate?
    bool getTerminate() const;

private:

    // Time source used to compare elapsed time against period
    std::chrono::steady_clock clock;

    // Length of time between step() executions
    std::chrono::nanoseconds period;

    // How close do we have to be to the start of frame time to be considered
    // at the start time
    std::chrono::nanoseconds tolerance;

    // Counts the number of completed step() executions
    long completed_iterations;

    // run() will exit if this is true
    bool terminate;

    // Used to track frame time used statistics during runtime
    OnlineStatistics statistics;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    FixedRateProgram(const FixedRateProgram&);
    FixedRateProgram& operator=(const FixedRateProgram&);
};

//==============================================================================
inline void FixedRateProgram::setPeriod(const std::chrono::nanoseconds& period)
{
    this->period = period;
}

//==============================================================================
inline void FixedRateProgram::getPeriod(std::chrono::nanoseconds& period) const
{
    period = this->period;
}

//==============================================================================
inline
void FixedRateProgram::setTolerance(const std::chrono::nanoseconds& tolerance)
{
    this->tolerance = tolerance;
}

//==============================================================================
inline
void FixedRateProgram::getTolerance(std::chrono::nanoseconds& tolerance) const
{
    tolerance = this->tolerance;
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
