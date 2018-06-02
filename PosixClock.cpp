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
