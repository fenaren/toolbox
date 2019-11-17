#if !defined FIXED_RATE_PROGRAM_INTERFACE_HPP
#define FIXED_RATE_PROGRAM_INTERFACE_HPP

#include <chrono>

#include "ProgramInterface.hpp"

class FixedRateProgramInterface : virtual public ProgramInterface
{
public:

    // Iterative code goes here
    virtual void step() = 0;

    // Sets length of time between step() executions
    virtual void setPeriod(const std::chrono::nanoseconds& period) = 0;

    // Returns length of time between step() executions
    virtual void getPeriod(std::chrono::nanoseconds& period) const = 0;

    // Sets allowable error between the ideal frame start time and the actual
    // frame start time
    virtual void setTolerance(const std::chrono::nanoseconds& tolerance) = 0;

    // Returns the allowable error between the ideal frame start time and actual
    // frame start time
    virtual void getTolerance(std::chrono::nanoseconds& tolerance) const = 0;

    // Setting to true will cause program termination before the next time
    // step() is called; a step() in progress is not interrupted
    virtual void setTerminate(bool terminate) = 0;

    // Is the program set to terminate?
    virtual bool getTerminate() const = 0;
};

#endif
