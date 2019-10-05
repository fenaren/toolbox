#if !defined CLOCK_IMPL_HPP
#define CLOCK_IMPL_HPP

class ClockImpl
{
public:

    explicit ClockImpl(int clock);

    // Does nothing
    ~ClockImpl();

    virtual void setClock(int clock);

    virtual int getClock() const;

    // Returns time duration from clock epoch in seconds
    virtual double getTime() const = 0;

    // Calling process sleeps for specified duration (in seconds)
    virtual void sleep(double time) = 0;

private:

    int clock;
};

//==============================================================================
inline void ClockImpl::setClock(int clock)
{
    this->clock = clock;
}

//==============================================================================
inline int ClockImpl::getClock() const
{
    return clock;
}

#endif
