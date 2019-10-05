#include "NoopClockImpl.hpp"

//==============================================================================
NoopClockImpl::NoopClockImpl(int clock_type) :
    ClockImpl(clock_type)
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
