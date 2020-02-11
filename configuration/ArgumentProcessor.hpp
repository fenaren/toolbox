#if !defined ARGUMENT_PROCESSOR_HPP
#define ARGUMENT_PROCESSOR_HPP

#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>

// Forward declarations
class ConfigurationValueBase;
template <class T> class ConfigurationValue;

// Implements a method of more easily processing command line arguments into
// actual in-program values.  The idea is to get rid of having to manually code
// the looping over arguments and comparing to known flags or positions in the
// argument list.
class ArgumentProcessor
{
public:

    friend class ArgumentProcessor_test;

    // Constructor
    ArgumentProcessor();

    // Destructor
    virtual ~ArgumentProcessor();

    // Registers a positional argument with the processor.  Order of
    // registration matters here; positional arguments are set in the order they
    // are registered.
    void registerPositionalArgument(ConfigurationValueBase* argument);

    // Registers an optional argument with the processor.  Unlike positional
    // arguments, registration order of optional arguments does not matter,
    // since conventionally optional arguments are identified by their flags,
    // not their position in the argument list.
    void registerOptionalArgument(
        ConfigurationValueBase*                argument,
        const std::unordered_set<std::string>& flags,
        bool                                   count);

    // Processes a single command-line argument.  If this is a positional
    // argument its value will be written into the next unset registered
    // positional argument.  If this is a flag for an optional argument,
    // ArgumentProcessor will expect the next argument given to represent the
    // value of the optional argument, or in the case of ConfigurationValue-type
    // arguments, will increment the count.
    void process(const std::string& argument);

    // Process multiple sequential arguments using the single-argument version
    // of process() above.
    void process(const std::list<std::string>& arguments);

    // For arguments straight off the command line.  Uses the single-argument
    // version of process() above.
    void process(int argc, char** argv);

private:

    std::list<ConfigurationValueBase*> positional_arguments;

    // Tracks the positional argument we're going to process next
    std::list<ConfigurationValueBase*>::iterator next_positional_argument;

    // Maps flags that take a value to their associated optional arguments.
    // Multiple flags will link to the same object for arguments with multiple
    // flags (ex. -v and --verbose).
    std::unordered_map<std::string, ConfigurationValueBase*> optional_arguments;

    // The optional value argument we're in the middle of processing
    std::unordered_map<std::string, ConfigurationValueBase*>::iterator
    current_optional_argument;

    // Maps flags that do not take a value to their associated optional
    // argument counts.  Multiple flags will link to the same object for
    // arguments with multiple flags (ex. -v and --verbose).
    std::unordered_map<std::string, ConfigurationValue<unsigned int>*>
    optional_argument_counts;

    ArgumentProcessor(const ArgumentProcessor& argument_processor);
    ArgumentProcessor& operator=(const ArgumentProcessor& argument_processor);
};

#endif
