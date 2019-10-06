#if !defined CLOCK_HPP
#define CLOCK_HPP

class ClockImpl;

class Clock
{
public:

    explicit Clock(int clock_type = 0);

    // Copy constructor
    Clock(const Clock& clock);

    // Does nothing
    ~Clock();

    virtual void setClockType(int clock_type);

    virtual int getClockType() const;

    // Returns time duration from clock epoch in seconds
    virtual double getTime() const;

    // Calling process sleeps for specified duration (in seconds)
    virtual void sleep(double time);

    // Assignment
    Clock& operator=(const Clock& clock);

protected:

    // Sets the platform-specific implementation to be used
    void setImplementation(ClockImpl* clock_impl);

    ClockImpl* getImplementation() const;

private:

    // A concrete implementation created by derived classes
    ClockImpl* clock_impl;
};

//==============================================================================
inline void Clock::setImplementation(ClockImpl* clock_impl)
{
    this->clock_impl = clock_impl;
}

//==============================================================================
inline ClockImpl* Clock::getImplementation() const
{
    return clock_impl;
}

#endif
