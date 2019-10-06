#include <stdexcept>

#include "Clock.hpp"

#include "ClockFactory.hpp"
#include "ClockImpl.hpp"
#include "misc.hpp"

//==============================================================================
Clock::Clock(int clock_type) :
    clock_impl(0)
{
    clock_impl = ClockFactory::createClock(clock_type);

    IF_NULL_THROW_ELSE_RUN(clock_impl,
                           "Platform-specific clock could not be created",
                           setImplementation(clock_impl));
}

//==============================================================================
Clock::Clock(const Clock& clock)
{
}

//==============================================================================
Clock::~Clock()
{
    delete clock_impl;
}

//==============================================================================
void Clock::setClockType(int clock_type)
{
    IF_NULL_THROW_ELSE_RUN(clock_impl,
                           "Platform-specific clock is not available",
                           clock_impl->setClockType(clock_type));
}

//==============================================================================
int Clock::getClockType() const
{
    IF_NULL_THROW_ELSE_RUN(clock_impl,
                           "Platform-specific clock is not available",
                           return clock_impl->getClockType());
}

//==============================================================================
double Clock::getTime() const
{
    IF_NULL_THROW_ELSE_RUN(clock_impl,
                           "Platform-specific clock is not available",
                           return clock_impl->getTime());
}

//==============================================================================
void Clock::sleep(double duration)
{
    IF_NULL_THROW_ELSE_RUN(clock_impl,
                           "Platform-specific clock is not available",
                           clock_impl->sleep(duration));
}

//==============================================================================
Clock& Clock::operator=(const Clock& clock)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &clock)
    {
        // Do something
    }

    return *this;
}
