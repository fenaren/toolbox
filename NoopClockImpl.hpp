#if !defined NOOP_CLOCK_IMPL_HPP
#define NOOP_CLOCK_IMPL_HPP

#include "ClockImpl.hpp"

class NoopClockImpl : public ClockImpl
{
public:

    explicit NoopClockImpl(int clock_type);

    // Does nothing
    virtual ~NoopClockImpl();

    // Returns time duration from clock epoch in seconds
    virtual double getTime() const;

    // Calling process sleeps for specified duration (in seconds)
    virtual void sleep(double duration);
};

#endif
