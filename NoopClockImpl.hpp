#if !defined NOOP_CLOCK_IMPL_HPP
#define NOOP_CLOCK_IMPL_HPP

#include "ClockImpl.hpp"

class NoopClockImpl : public ClockImpl
{
public:

    explicit NoopClockImpl(int clock);

    // Does nothing
    ~NoopClockImpl();

    // Returns time duration from clock epoch in seconds
    virtual double getTime() const;

    // Calling process sleeps for specified duration (in seconds)
    virtual void sleep(double time);
};

#endif
