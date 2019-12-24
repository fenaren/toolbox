#if !defined ARGUMENT_PROCESSOR_HPP
#define ARGUMENT_PROCESSOR_HPP

#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

class OptionalArgument;
class OptionalValueArgument;
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

    // Maps optional arguments that DO NOT themselves have values to their
    // representative objects. Multiple flags will link to the same object for
    // arguments with multiple flags (ex. -v and --verbose).
    OptionalArgumentsMap optional_arguments;

    typedef std::unordered_map<std::string,
                               std::shared_ptr<OptionalValueArgument> >
    OptionalValueArgumentsMap;

    // Maps optional arguments that DO have values to their representative
    // objects. Multiple flags will link to the same object for arguments with
    // multiple flags (ex. -v and --verbose).
    OptionalValueArgumentsMap optional_value_arguments;

    // The optional value argument we're in the middle of processing
    OptionalValueArgumentsMap::iterator current_optional_value_argument;
};

#endif
