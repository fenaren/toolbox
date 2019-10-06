#if !defined CLOCK_FACTORY_HPP
#define CLOCK_FACTORY_HPP

class ClockImpl;

// Provides a platform-independent way of acquiring platform-specific clocks
class ClockFactory
{
public:

    // The interface through which platform-specific signal managers are
    // acquired.
    static ClockImpl* createClock(int clock_type);

private:

    // Disallowed, only static functions here
    ClockFactory();
    ~ClockFactory();
    ClockFactory(const ClockFactory&);
    ClockFactory& operator=(const ClockFactory&);
};

#endif
