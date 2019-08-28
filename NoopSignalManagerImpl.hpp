#if !defined NOOP_SIGNAL_MANAGER_IMPL_HPP
#define NOOP_SIGNAL_MANAGER_IMPL_HPP

#include <string>
#include <unordered_set>

class NoopSignalManagerImpl : public SignalManagerImpl
{
public:

    // These do nothing
    NoopSignalManagerImpl();
    virtual ~NoopSignalManagerImpl();

    // Does nothing.  See the base class for a description of what this is
    // supposed to do in a meaningful implementation.
    virtual bool registerSignal(int sig);

    // Does nothing.  See the base class for a description of what this is
    // supposed to do in a meaningful implementation.
    virtual void signal(int sig);

    // Does nothing.  See the base class for a description of what this is
    // supposed to do in a meaningful implementation.
    virtual bool isSignalDelivered(int sig);

    // Does nothing.  See the base class for a description of what this is
    // supposed to do in a meaningful implementation.
    virtual
    void getSupportedSignals(std::unordered_set<int>& supported_signals);

    // Does nothing.  See the base class for a description of what this is
    // supposed to do in a meaningful implementation.
    virtual void getSignalName(int sig, std::string& signal_name);

private:

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    NoopSignalManagerImpl(const NoopSignalManagerImpl&);
    NoopSignalManagerImpl& operator=(const NoopSignalManagerImpl&);
};

#endif
