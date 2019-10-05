#include <cerrno>
#include <ctime>
#include <stdexcept>
#include <system_error>

#include "PosixClockImpl.hpp"

#include "PosixTimespec.hpp"

//==============================================================================
PosixClockImpl::PosixClockImpl(int clock_type) :
    ClockImpl(clock_type),
    clock_id(static_cast<clockid_t>(clock_type))
{
}

//==============================================================================
PosixClockImpl::PosixClockImpl(const PosixClockImpl& posix_clock_impl)
{
    *this = posix_clock_impl;
}

//==============================================================================
PosixClockImpl::~PosixClockImpl()
{
}

//==============================================================================
double PosixClockImpl::getTime() const
{
    // Get the time in the specific way and then generalize
    PosixTimespec ts;
    getTime(ts);
    return ts.toDouble();
}

//==============================================================================
void PosixClockImpl::getTime(PosixTimespec& ts) const
{
    timespec tp;
    if (clock_gettime(clock_id, &tp) != 0)
    {
        throw std::system_error(errno, std::system_category());
    }

    ts = tp;
}

//==============================================================================
void PosixClockImpl::sleep(double duration)
{
    // Convert to the specific way we sleep here and then sleep
    PosixTimespec ts(duration);
    sleep(duration);
}

//==============================================================================
void PosixClockImpl::sleep(const PosixTimespec& ts)
{
    timespec tp;
    ts.getTimespec(tp);

#if defined MACOS
    // clock_nanosleep isn't implemented on macOS?
    int sleep_ret = ::nanosleep(&tp, 0);
#else
    int sleep_ret = clock_nanosleep(clock_id, 0, &tp, 0);
#endif

    if (sleep_ret != 0)
    {
        throw std::system_error(errno, std::system_category());
    }
}

//==============================================================================
PosixClockImpl& PosixClockImpl::operator=(const PosixClockImpl& posix_clock)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &posix_clock)
    {
        clock_id = posix_clock.getClockId();
    }

    return *this;
}
