#include "NoopClockImpl.hpp"

//==============================================================================
NoopClockImpl::NoopClockImpl(int clock) :
    ClockImpl(clock)
{
}

//==============================================================================
NoopClockImpl::~NoopClockImpl()
{
}

//==============================================================================
double NoopClockImpl::getTime() const
{
    return 0.0;
}

//==============================================================================
void NoopClockImpl::sleep(double time)
{
}
