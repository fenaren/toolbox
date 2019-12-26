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

    virtual ~ArgumentProcessor();

    void registerPositionalArgument(const std::string& name);

    void registerOptionalArgument(
        const std::string&                     name,
        const std::unordered_set<std::string>& flags,
        bool                                   has_a_value);

    // Process a single argument
    void process(const std::string& argument);

    // Process multiple sequential arguments
    void process(const std::list<std::string>& arguments);

    // For arguments straight off the command line
    void process(int argc, char** argv);

private:

    void checkNamemapsForDuplicate(const std::string& name) const;
    void checkFlagmapsForDuplicate(const std::string& flag) const;

    typedef std::list<std::shared_ptr<PositionalArgument> >
    PositionalArgumentList;

    PositionalArgumentList positional_arguments_list;

    typedef std::unordered_map<std::string,
                               std::shared_ptr<PositionalArgument> >
    PositionalArgumentNameMap;

    PositionalArgumentNameMap positional_arguments_namemap;

    // Tracks the positional argument we're going to process next
    PositionalArgumentList::iterator next_positional_argument;

    typedef std::unordered_map<std::string, std::shared_ptr<OptionalArgument> >
    OptionalArgumentsMap;

    // Maps optional arguments that DO NOT themselves have values to their
    // representative objects. Multiple flags will link to the same object for
    // arguments with multiple flags (ex. -v and --verbose).
    OptionalArgumentsMap optional_arguments_namemap;
    OptionalArgumentsMap optional_arguments_flagmap;

    typedef std::unordered_map<std::string,
                               std::shared_ptr<OptionalValueArgument> >
    OptionalValueArgumentsMap;

    // Maps optional arguments that DO have values to their representative
    // objects. Multiple flags will link to the same object for arguments with
    // multiple flags (ex. -v and --verbose).
    OptionalValueArgumentsMap optional_value_arguments_namemap;
    OptionalValueArgumentsMap optional_value_arguments_flagmap;

    // The optional value argument we're in the middle of processing
    OptionalValueArgumentsMap::iterator current_optional_value_argument;

    ArgumentProcessor(const ArgumentProcessor& argument_processor);
    ArgumentProcessor& operator=(const ArgumentProcessor& argument_processor);
};

#endif
