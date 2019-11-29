#if !defined FIXED_RATE_PROGRAM_INTERFACE_HPP
#define FIXED_RATE_PROGRAM_INTERFACE_HPP

#include <chrono>

#include "ProgramInterface.hpp"

// Defines the API for FixedRatePrograms.  See the FixedRateProgram header for
// documentation.
class FixedRateProgramInterface : virtual public ProgramInterface
{
public:

    virtual void step() = 0;

    virtual void setPeriod(const std::chrono::nanoseconds& period) = 0;

    virtual void getPeriod(std::chrono::nanoseconds& period) const = 0;

    virtual void setTolerance(const std::chrono::nanoseconds& tolerance) = 0;

    virtual void getTolerance(std::chrono::nanoseconds& tolerance) const = 0;

    virtual void setTerminate(bool terminate) = 0;

    virtual bool getTerminate() const = 0;
};

#endif
