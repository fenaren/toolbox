#if !defined SIGNAL_MANAGER_HPP
#define SIGNAL_MANAGER_HPP

class SignalManager
{
public:

    // Nothing to do here
    SignalManager();
    virtual ~SignalManager();

    // C function "cfun" is assigned to handle signals of type sig
    virtual bool registerSignalHandler(int sig, void cfun(int)) = 0;

    // External sources can use this interface to signal this program; signals
    // are not handled immediately, they are placed on a list and handled within
    // the processDeliveredSignals member function
    virtual void signal(int sig) = 0;

    // Returns true if sig has been delivered
    virtual bool isSignalDelivered(int sig) = 0;
};

#endif
