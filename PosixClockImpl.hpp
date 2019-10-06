#if !defined POSIX_CLOCK_IMPL_HPP
#define POSIX_CLOCK_IMPL_HPP

#include <time.h>

#include "ClockImpl.hpp"

#include "PosixTimespec.hpp"

class PosixClockImpl : public ClockImpl
{
public:

    // Saves user specified clock
    explicit PosixClockImpl(int clock_type);

    // Does nothing
    virtual ~PosixClockImpl();

    // Saves user specified POSIX clock
    virtual void setClockType(int clock_type);

    // Returns POSIX clock in use
    virtual int getClockType() const;

    // Returns time according to the users previously specified clock and the
    // POSIX clock_gettime function
    double getTime() const;
    void getTime(PosixTimespec& ts) const;

    // Caling process nanosleeps for specified length of time
    void sleep(double duration);
    void sleep(const PosixTimespec& ts);

private:

    // Currently selected POSIX clock source
    clockid_t clock_id;

    // Copy constructor
    PosixClockImpl(const PosixClockImpl&);
    PosixClockImpl& operator=(const PosixClockImpl&);
};

//==============================================================================
inline void PosixClockImpl::setClockType(int clock_type)
{
    ClockImpl::setClockType(clock_type);

    // Store a more specific reference here, where we know this is how clocks
    // are identified for POSIX
    this->clock_id = static_cast<clockid_t>(clock_type);
}

//==============================================================================
inline int PosixClockImpl::getClockType() const
{
    return static_cast<int>(clock_id);
}

#endif
