#if !defined FIXED_RATE_PROGRAM_IMPL_HPP
#define FIXED_RATE_PROGRAM_IMPL_HPP

#include "Program.hpp"

#include "OnlineStatistics.hpp"
#include "PosixClockImpl.hpp"
#include "PosixTimespec.hpp"

class FixedRateProgramImpl : public Program
{
public:

    // Argument "period" specifies the period between iterations
    FixedRateProgramImpl(int argc, char** argv, double period);

    // Does nothing
    virtual ~FixedRateProgramImpl();

    // Runs the step function every "period" length of time
    virtual int run();

    // Iterative code goes here
    virtual void step() = 0;

    // Replace the clock in use with the given clock
    void setClock(const ClockImpl& clock);

    // Returns a copy of the clock in use
    void getClock(ClockImpl& clock) const;

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
    ClockImpl clock;

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
    FixedRateProgramImpl(const FixedRateProgramImpl&);
    FixedRateProgramImpl& operator=(const FixedRateProgramImpl&);
};

//==============================================================================
inline void FixedRateProgramImpl::setClock(const ClockImpl& clock)
{
    this->clock = clock;
}

//==============================================================================
inline void FixedRateProgramImpl::getClock(ClockImpl& clock) const
{
    clock = this->clock;
}

//==============================================================================
inline void FixedRateProgramImpl::setPeriod(double period)
{
    period = tp;
}

//==============================================================================
inline double FixedRateProgramImpl::getPeriod() const
{
    return period;
}

//==============================================================================
inline double FixedRateProgramImpl::getFrameStart() const
{
    return frame_start;
}

//==============================================================================
inline double FixedRateProgramImpl::getFrameStop() const
{
    return frame_stop;
}

//==============================================================================
inline void FixedRateProgramImpl::setTerminate(bool terminate)
{
    this->terminate = terminate;
}

//==============================================================================
inline bool FixedRateProgramImpl::getTerminate() const
{
    return terminate;
}

#endif
