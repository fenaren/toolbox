#if !defined ARGUMENT_PROCESSOR_HPP
#define ARGUMENT_PROCESSOR_HPP

#include <list>
#include <string>
#include <unordered_map>

#include "Argument.hpp"

class PositionalArgument;

class ArgumentProcessor : public Argument
{
public:

    friend class ArgumentProcessor_test;

    ArgumentProcessor(const std::string& name,
                      const std::string& description = "");

    ArgumentProcessor(const ArgumentProcessor& argument_processor);

    virtual ~ArgumentProcessor();

    void registerPositionalArgument(const std::string& name,
                                    const std::string& description);

    /*void registerOptionalArgument(
        const std::string&                     name,
        const std::string&                     description,
        const std::unordered_set<std::string>& aliases =
        std::unordered_set<std::string>());*/

    // Registers a positional argument representing the name the program was
    // invoked with at the command line.  Program name is always the first
    // argument, so chances are you'll want to have this registered as the first
    // positional argument.  This method is called at construction time to help
    // with this.
    //void registerName();

    // Un-registers all registered arguments.  After a call to this no arguments
    // will be recognized, including the usual first argument representing the
    // name the program was invoked with at the command line.  It is possible to
    // register arguments after a call to this (calling registerName() might be
    // a good idea).
    //void unregisterAll();

    virtual bool isSpecified() const;

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

    std::unordered_map<std::string, ArgumentProcessor> optional_arguments;

    // Tracks the positional argument we're going to process next
    std::list<PositionalArgument>::iterator next_positional_argument;

    // Tracks the optional argument we're in the middle of processing, if there
    // is one
    std::unordered_map<std::string, ArgumentProcessor>::iterator
    current_optional_argument;

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
