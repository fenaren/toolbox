#if !defined CLOCK_IMPL_HPP
#define CLOCK_IMPL_HPP

class ClockImpl
{
public:

    explicit ClockImpl(int clock_type);

    // Does nothing
    virtual ~ClockImpl();

    virtual void setClockType(int clock_type);

    virtual int getClockType() const;

    // Returns time duration from clock epoch in seconds
    virtual double getTime() const = 0;

    // Calling process sleeps for specified duration (in seconds)
    virtual void sleep(double time) = 0;

private:

    int clock_type;
};

//==============================================================================
inline void ClockImpl::setClockType(int clock_type)
{
    this->clock_type = clock_type;
}

//==============================================================================
inline int ClockImpl::getClockType() const
{
    return clock_type;
}

#endif
