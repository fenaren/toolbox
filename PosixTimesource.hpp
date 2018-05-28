#if !defined POSIX_TIMESOURCE_HPP
#define POSIX_TIMESOURCE_HPP

#include <time.h>

#include "PosixTimespec.hpp"

class PosixTimesource
{
public:

    explicit PosixTimesource(clockid_t clk_id);

    ~PosixTimesource();

    int getCurrentTime(PosixTimespec& ts) const;

    void setClockId(clockid_t clk_id);

    clockid_t getClockId() const;

private:

    // Currently selected POSIX clock source
    clockid_t clk_id;
};

inline void PosixTimesource::setClockId(clockid_t clk_id)
{
    this->clk_id = clk_id;
}

inline clockid_t PosixTimesource::getClockId() const
{
    return clk_id;
}

#endif
