#include "ClockFactory.hpp"

#if defined LINUX || MACOS
#include "PosixClockImpl.hpp"
#elif defined WINDOWS
#include "NoopClockImpl.hpp"
#endif

//=============================================================================
ClockImpl* ClockFactory::createClock(int clock_type)
{
#if defined LINUX || MACOS
    return new PosixClockImpl(clock_type);
#else
    // Should be replaced with a proper implementation
    return new NoopClockImpl(clock_type);
#endif
}
