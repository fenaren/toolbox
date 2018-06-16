#if !defined PROGRAM_HPP
#define PROGRAM_HPP

#include <csignal>
#include <pthread.h>
#include <string>
#include <utility>
#include <vector>

class Program
{
public:

    // Argument parsing and program initialization happens here
    Program(int argc, char** argv);

    // Nothing to do on shutdown here
    virtual ~Program();

    // Derived programs implement the program in here
    virtual int run() = 0;

    // THREAD-SAFE; External sources can use this interface to signal this
    // program; signals are not handled immediately, they are placed on a list
    // and handled within the processSignals member function
    void signal(int sig);

    // Returns a copy of the program name
    void getName(std::string& name) const;

    // Returns a copy of the program arguments
    void getArguments(std::vector<std::string>& arguments) const;

    // THREAD-SAFE; Returns a copy of the set of delivered signals
    void getDeliveredSignals(sigset_t& sigset);

    // THREAD-SAFE; Returns true if sig has been delivered
    bool isSignalDelivered(int sig);

    // C function "cfun" is assigned to handle signals of type sig
    static bool attachSignal(int sig, void cfun(int));

    // Reconfigure self as a background process (daemon); this may be a behavior
    // that only makes sense to implement at this level on Linux systems, not
    // sure
    static bool daemonize();

protected:

    // Derived classes should implement this function with their signal handling
    // code; get the current set of delivered signals by calling
    // getDeliveredSignals() or check if a particular signal is delivered using
    // isSignalDelivered(); after signals are processed use unsignal() or
    // unsignalAll() to mark signals as processed
    virtual void processDeliveredSignals();

    // THREAD-SAFE; Removes a particular signal from the set of delivered
    // signals
    void unsignal(int sig);

    // THREAD-SAFE; Removes all signals from the set of delivered signals
    void unsignalAll();

private:

    // String used to launch this program at the command line
    std::string name;

    // Arguments given to the program at runtime
    std::vector<std::string> arguments;

    // Received signals line up here
    sigset_t delivered_signals;

    // Provides mutually exclusive access to delivered_signals
    pthread_mutex_t delivered_signals_mutex;
};

#endif
