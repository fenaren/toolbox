#if !defined FIXED_RATE_PROGRAM
#define FIXED_RATE_PROGRAM

#include "Program.hpp"

#include "OnlineStatistics.hpp"
#include "PosixClock.hpp"
#include "PosixTimespec.hpp"

class FixedRateProgram : public Program
{
public:

    // Argument period specifies the period between iterations
    FixedRateProgram(int argc, char** argv, const PosixTimespec& period);

    virtual ~FixedRateProgram();

    // Runs the step function every "period" length of time
    virtual int run();

    // Iterative code goes here
    virtual void step() = 0;

    // Replace the clock in use with the given clock
    void setClock(const PosixClock& clock);

    // Returns a copy of the clock in use
    void getClock(PosixClock& clock) const;

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
    PosixClock clock;

    // Length of time between iterations
    PosixTimespec period;

    // Updated at the beginning and ending of the frame, respectively
    PosixTimespec frame_start;
    PosixTimespec frame_stop;

    // Iterative loop will exit if this is true
    bool terminate;

    // Tracks frame time used statistics during runtime
    OnlineStatistics statistics;
};

inline void FixedRateProgram::setClock(const PosixClock& clock)
{
    this->clock = clock;
}

inline void FixedRateProgram::getClock(PosixClock& clock) const
{
    clock = this->clock;
}

inline void FixedRateProgram::setPeriod(const PosixTimespec& tp)
{
    period = tp;
}

inline void FixedRateProgram::getPeriod(PosixTimespec& tp) const
{
    tp = period;
}

inline void FixedRateProgram::getFrameStart(PosixTimespec& tp) const
{
    tp = frame_start;
}

inline void FixedRateProgram::getFrameStop(PosixTimespec& tp) const
{
    tp = frame_stop;
}

inline void FixedRateProgram::setTerminate(bool terminate)
{
    this->terminate = terminate;
}

inline bool FixedRateProgram::getTerminate() const
{
    return terminate;
}

#endif
