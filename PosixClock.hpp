#if !defined POSIX_CLOCK_HPP
#define POSIX_CLOCK_HPP

#include <time.h>

#include "PosixTimespec.hpp"

class PosixClock
{
public:

    // Saves user specified clock
    explicit PosixClock(clockid_t clk_id);

    // Does nothing
    ~PosixClock();

    // Returns time according to the users previously specified clock and the
    // POSIX clock_gettime function
    void getTime(PosixTimespec& ts) const;

    // Saves user specified POSIX clock
    void setClockId(clockid_t clk_id);

    // Returns POSIX clock in use
    clockid_t getClockId() const;

    // Caling process nanosleeps for specified length of time
    void nanosleep(const PosixTimespec& ts);

private:

    // Currently selected POSIX clock source
    clockid_t clk_id;
};

inline void PosixClock::setClockId(clockid_t clk_id)
{
    this->clk_id = clk_id;
}

inline clockid_t PosixClock::getClockId() const
{
    return clk_id;
}

#endif
