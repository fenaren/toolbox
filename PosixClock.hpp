#if !defined POSIX_CLOCK_HPP
#define POSIX_CLOCK_HPP

#include <time.h>

#include "PosixTimespec.hpp"

class PosixClock
{
public:

    explicit PosixClock(clockid_t clk_id);

    ~PosixClock();

    int getTime(PosixTimespec& ts) const;

    void setClockId(clockid_t clk_id);

    clockid_t getClockId() const;

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
