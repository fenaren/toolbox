#if !defined POSIX_CLOCK_IMPL_HPP
#define POSIX_CLOCK_IMPL_HPP

#include <time.h>

#include "ClockImpl.hpp"

#include "PosixTimespec.hpp"

class PosixClockImpl : public ClockImpl
{
public:

    // Saves user specified clock
    explicit PosixClockImpl(clockid_t clk_id);

    // Copy constructor
    PosixClockImpl(const PosixClockImpl&);

    // Does nothing
    ~PosixClockImpl();

    // Returns time according to the users previously specified clock and the
    // POSIX clock_gettime function
    void getTime(PosixTimespec& ts) const;

    // Saves user specified POSIX clock
    void setClockId(clockid_t clk_id);

    // Returns POSIX clock in use
    clockid_t getClockId() const;

    // Caling process nanosleeps for specified length of time
    void nanosleep(const PosixTimespec& ts);

    PosixClockImpl& operator=(const PosixClockImpl&);

private:

    // Currently selected POSIX clock source
    clockid_t clk_id;
};

inline void PosixClockImpl::setClockId(clockid_t clk_id)
{
    this->clk_id = clk_id;
}

inline clockid_t PosixClockImpl::getClockId() const
{
    return clk_id;
}

#endif
