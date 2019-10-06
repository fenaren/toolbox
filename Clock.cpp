#include <stdexcept>

#include "Clock.hpp"

#include "ClockFactory.hpp"
#include "ClockImpl.hpp"

#define IF_NULL_THROW_ELSE_RUN(possibly_null, null_desc, statement)     \
    if (possibly_null)                                                  \
    {                                                                   \
        statement;                                                      \
    }                                                                   \
    else                                                                \
    {                                                                   \
        throw std::runtime_error(null_desc);                            \
    }

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
