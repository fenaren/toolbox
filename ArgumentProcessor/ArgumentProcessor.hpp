#if !defined ARGUMENT_PROCESSOR_HPP
#define ARGUMENT_PROCESSOR_HPP

#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Argument.hpp"

class PositionalArgument;

class ArgumentProcessor : public Argument
{
public:

    friend class ArgumentProcessor_test;

    ArgumentProcessor(const std::string& name        = "",
                      const std::string& description = "");

    ArgumentProcessor(const ArgumentProcessor& argument_processor);

    virtual ~ArgumentProcessor();

    void registerPositionalArgument(const std::string& name,
                                    const std::string& description = "");

    void registerOptionalArgument(
        const std::string&                     name,
        const std::string&                     description,
        const std::unordered_set<std::string>& flags);

    // Has this argument been specified?
    virtual bool isSpecified() const;

    // Internal state is set to what it would be after initial construction.
    virtual void reset();

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

    typedef std::unordered_map<std::string, std::shared_ptr<ArgumentProcessor> >
    OptionalArgumentsMap;

    OptionalArgumentsMap optional_arguments;

    // Tracks the optional argument we're in the middle of processing, if there
    // is one
    OptionalArgumentsMap::iterator current_optional_argument;

    // Maps argument names to their corresponding values.  Multiple names will
    // link to the same value for arguments with multiple names (ex. -v and
    // --verbose).  A single copy of the actual value for each argument is
    // stored in the argument_values map.
    //std::unordered_map<std::string, std::string*> canonical_names;

    //std::unordered_set<std::string> canonical_names;
};

//==============================================================================
/*inline void ArgumentProcessor::registerName()
{
    registerPositionalArgument(
        "Name",
        "Name the program was invoked with at the command line");
        }*/

//==============================================================================
/*inline void ArgumentProcessor::unregisterAll()
{
    positional_arguments.clear();
    optional_arguments.clear();
    }*/

#endif
