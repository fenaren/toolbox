#include <time.h>

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
int PosixClock::getTime(PosixTimespec& ts) const
{
    timespec tp;
    int cg_ret = clock_gettime(clk_id, &tp);

    ts = tp;

    return cg_ret;
}

//==============================================================================
// Calling process sleeps for specified length of time
//==============================================================================
// cppcheck-suppress functionStatic
void PosixClock::nanosleep(const PosixTimespec& ts)
{
    timespec tp;
    ts.getTimespec(tp);

#if defined MACOS
    // clock_nanosleep isn't implemented on macOS?
    ::nanosleep(&tp, 0);
#else
    clock_nanosleep(clk_id, 0, &tp, 0);
#endif
}
