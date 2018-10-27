#if !defined SIGNAL_MANAGER_FACTORY_HPP
#define SIGNAL_MANAGER_FACTORY_HPP

class SignalManagerImpl;

// Provides a platform-independent way of acquiring platform-specific signal
// managers.
class SignalManagerFactory
{
public:

    // The interface through which platform-specific signal managers are
    // acquired.
    static SignalManagerImpl* createSignalManager();

private:

    // Disallowed
    SignalManagerFactory();
    ~SignalManagerFactory();
};

#endif
