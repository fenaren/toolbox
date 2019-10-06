#if !defined CLOCK_HPP
#define CLOCK_HPP

class ClockImpl;

class Clock
{
public:

    explicit Clock(int clock_type);

    // Does nothing
    ~Clock();

    virtual void setClockType(int clock_type);

    virtual int getClockType() const;

    // Returns time duration from clock epoch in seconds
    virtual double getTime() const;

    // Calling process sleeps for specified duration (in seconds)
    virtual void sleep(double time);

protected:

    // Sets the platform-specific implementation to be used
    void setImplementation(ClockImpl* clock_impl);

private:

    // A concrete implementation created by derived classes
    ClockImpl* clock_impl;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    Clock(const Clock&);
    Clock& operator=(const Clock&);
};

//==============================================================================
inline void Clock::setImplementation(ClockImpl* clock_impl)
{
    this->clock_impl = clock_impl;
}

#endif
