#if !defined POSIX_TIME_HPP
#define POSIX_TIME_HPP

#include <time.h>

#include "PosixTimestamp.hpp"

class PosixTime
{
public:

    PosixTime(const clockid_t& clk_id);

    int getCurrentTime(PosixTimestamp& ts);

    void setClockId(const clockid_t& clk_id);

    void getClockId(clockid_t& clk_id);

private:

    clockid_t clk_id;
};

#endif
