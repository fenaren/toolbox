#include <cerrno>
#include <ctime>
#include <stdexcept>
#include <system_error>

#include "PosixClock.hpp"

#include "PosixTimespec.hpp"

//==============================================================================
// Saves user specified clock
//==============================================================================
PosixClock::PosixClock(clockid_t clk_id) :
    clk_id(clk_id)
{
}

//==============================================================================
// Does nothing
//==============================================================================
PosixClock::~PosixClock()
{
}

//==============================================================================
// Returns time according to the users previously specified clock
//==============================================================================
void PosixClock::getTime(PosixTimespec& ts) const
{
    timespec tp;
    if (clock_gettime(clk_id, &tp) != 0)
    {
        throw std::system_error(errno, std::system_category());
    }

    ts = tp;
}

//==============================================================================
// Calling process sleeps for specified length of time
//==============================================================================
void PosixClock::nanosleep(const PosixTimespec& ts)
{
    timespec tp;
    ts.getTimespec(tp);

#if defined MACOS
    // clock_nanosleep isn't implemented on macOS?
    int sleep_ret = ::nanosleep(&tp, 0);
#else
    int sleep_ret = clock_nanosleep(clk_id, 0, &tp, 0);
#endif

    if (sleep_ret != 0)
    {
        throw std::system_error(errno, std::system_category());
    }
}
