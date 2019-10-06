#if !defined POSIX_FIXED_RATE_PROGRAM_IMPL_HPP
#define POSIX_FIXED_RATE_PROGRAM_IMPL_HPP

#include "Program.hpp"

#include "OnlineStatistics.hpp"
#include "PosixClockImpl.hpp"
#include "PosixTimespec.hpp"

class PosixFixedRateProgramImpl : public Program
{
public:

    // Argument "period" specifies the period between iterations
    PosixFixedRateProgramImpl(
        int argc, char** argv, const PosixTimespec& period);

    // Does nothing
    virtual ~PosixFixedRateProgramImpl();

    // Runs the step function every "period" length of time
    virtual int run();

    // Iterative code goes here
    virtual void step() = 0;

    // Replace the clock in use with the given clock
    void setClock(const PosixClockImpl& clock);

    // Returns a copy of the clock in use
    void getClock(PosixClockImpl& clock) const;

    // Sets length of time between iterations as a PosixTimespec
    void setPeriod(const PosixTimespec& tp);

    // Returns length of time between iterations as a PosixTimespec
    void getPeriod(PosixTimespec& tp) const;

    // Returns the last time a frame started and stopped, respectively
    void getFrameStart(PosixTimespec& tp) const;
    void getFrameStop(PosixTimespec& tp) const;

    // Setting to true will cause program termination before the next time
    // step() is called; a step() in progress is not interrupted
    void setTerminate(bool terminate);

    // Is the program set to terminate?
    bool getTerminate() const;

private:

    // Time source used to compare elapsed time against period
    PosixClockImpl clock;

    // Length of time between iterations
    PosixTimespec period;

    // Updated at the beginning and ending of the frame, respectively
    PosixTimespec frame_start;
    PosixTimespec frame_stop;

    // Iterative loop will exit if this is true
    bool terminate;

    // Tracks frame time used statistics during runtime
    OnlineStatistics statistics;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    PosixFixedRateProgramImpl(const PosixFixedRateProgramImpl&);
    PosixFixedRateProgramImpl& operator=(const PosixFixedRateProgramImpl&);
};

//==============================================================================
inline void PosixFixedRateProgramImpl::setClock(const PosixClockImpl& clock)
{
    this->clock = clock;
}

//==============================================================================
inline void PosixFixedRateProgramImpl::getClock(PosixClockImpl& clock) const
{
    clock = this->clock;
}

//==============================================================================
inline void PosixFixedRateProgramImpl::setPeriod(const PosixTimespec& tp)
{
    period = tp;
}

//==============================================================================
inline void PosixFixedRateProgramImpl::getPeriod(PosixTimespec& tp) const
{
    tp = period;
}

//==============================================================================
inline void PosixFixedRateProgramImpl::getFrameStart(PosixTimespec& tp) const
{
    tp = frame_start;
}

//==============================================================================
inline void PosixFixedRateProgramImpl::getFrameStop(PosixTimespec& tp) const
{
    tp = frame_stop;
}

//==============================================================================
inline void PosixFixedRateProgramImpl::setTerminate(bool terminate)
{
    this->terminate = terminate;
}

//==============================================================================
inline bool PosixFixedRateProgramImpl::getTerminate() const
{
    return terminate;
}

#endif
