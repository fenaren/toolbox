#if !defined CONFIGURATION_ARGUMENT_PROCESSOR_HPP
#define CONFIGURATION_ARGUMENT_PROCESSOR_HPP

#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace Configuration
{
    class ParameterBase;
    template <class T> class Parameter;

    // Implements a method of more easily processing command line arguments into
    // actual in-program values.  The idea is to get rid of having to manually
    // code the looping over arguments and comparing to known flags or positions
    // in the argument list.
    class ArgumentProcessor
    {
    public:

        friend class ArgumentProcessor_test;

        // Constructor
        ArgumentProcessor();

        // Destructor
        ~ArgumentProcessor();

        // Registers a positional argument with the processor.  Order of
        // registration matters here; positional arguments are set in the order
        // they are registered.
        void registerPositionalArgument(ParameterBase* argument);

        // Registers an optional argument with the processor.  Unlike positional
        // arguments, registration order of optional arguments does not matter,
        // since conventionally optional arguments are identified by their
        // flags, not their position in the argument list.  Optional arguments
        // registered with this method take a single value.
        void registerOptionalArgument(
            ParameterBase*                         argument,
            const std::unordered_set<std::string>& flags);

        // Registers an optional argument with the processor.  Unlike positional
        // arguments, registration order of optional arguments does not matter,
        // since conventionally optional arguments are identified by their
        // flags, not their position in the argument list.  Optional arguments
        // registered with this method do not take a value; instead, the number
        // of times the argument flag appears is counted and stored as the
        // value.
        void registerOptionalCountingArgument(
            Parameter<unsigned int>*               argument,
            const std::unordered_set<std::string>& flags);

        // Processes a single command-line argument.  If this is a positional
        // argument its value will be written into the next unset registered
        // positional argument.  If this is a flag for an optional argument,
        // ArgumentProcessor will expect the next argument given to represent
        // the value of the optional argument, or in the case of Parameter-type
        // arguments, will increment the count.
        void process(const std::string& argument);

        // Process multiple sequential arguments using the single-argument
        // version of process() above.
        void process(const std::list<std::string>& arguments);

        // For arguments straight off the command line.  Uses the
        // single-argument version of process() above.
        void process(int argc, char** argv);

    private:

        std::list<ParameterBase*> positional_arguments;

        // Tracks the positional argument we're going to process next
        std::list<ParameterBase*>::iterator next_positional_argument;

        // Maps flags that take a value to their associated optional arguments.
        // Multiple flags will link to the same object for arguments with
        // multiple flags (ex. -v and --verbose).
        std::unordered_map<std::string, ParameterBase*> optional_arguments;

        // The optional value argument we're in the middle of processing
        std::unordered_map<std::string, ParameterBase*>::iterator
        current_optional_argument;

        // Maps flags that do not take a value to their associated optional
        // argument counts.  Multiple flags will link to the same object for
        // arguments with multiple flags (ex. -v and --verbose).
        std::unordered_map<std::string, Parameter<unsigned int>*>
        optional_counting_arguments;

        bool isRegistered(const ParameterBase* parameter) const;

        ArgumentProcessor(const ArgumentProcessor& argument_processor);
        ArgumentProcessor&
        operator=(const ArgumentProcessor& argument_processor);
    };

}

#endif
