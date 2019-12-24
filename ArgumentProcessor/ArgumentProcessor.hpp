#if !defined ARGUMENT_PROCESSOR_HPP
#define ARGUMENT_PROCESSOR_HPP

#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

class OptionalArgument;
class PositionalArgument;

class ArgumentProcessor
{
public:

    friend class ArgumentProcessor_test;

    ArgumentProcessor();

    ArgumentProcessor(const ArgumentProcessor& argument_processor);

    virtual ~ArgumentProcessor();

    void registerPositionalArgument(const std::string& name,
                                    const std::string& description = "");

    void registerOptionalArgument(
        const std::string&                     name,
        const std::string&                     description,
        const std::unordered_set<std::string>& flags,
        bool                                   has_a_value);

    // Internal state is set to what it would be after initial construction.
    virtual void reset();

    // Has this argument been specified?
    virtual bool isSpecified() const;

    // Process a single argument
    void process(const std::string& argument);

    // Process multiple sequential arguments
    void process(const std::list<std::string>& arguments);

    // For arguments straight off the command line
    void process(int argc, char** argv);

    ArgumentProcessor& operator=(const ArgumentProcessor& argument_processor);

private:

    std::list<PositionalArgument> positional_arguments;

    // Tracks the positional argument we're going to process next
    std::list<PositionalArgument>::iterator next_positional_argument;

    typedef std::unordered_map<std::string, std::shared_ptr<OptionalArgument> >
    OptionalArgumentsMap;

    // Maps optional argument flags to their corresponding processors.  Multiple
    // flags will link to the same processor for arguments with multiple flags
    // (ex. -v and --verbose).  Only a single copy of the actual processor for
    // each argument is stored.
    OptionalArgumentsMap optional_arguments;

    // Tracks the optional argument we're in the middle of processing, if there
    // is one
    OptionalArgumentsMap::iterator current_optional_argument;
};

#endif
