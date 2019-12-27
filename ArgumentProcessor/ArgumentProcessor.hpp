#if !defined ARGUMENT_PROCESSOR_HPP
#define ARGUMENT_PROCESSOR_HPP

#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Argument.hpp"

class ArgumentProcessor
{
public:

    friend class ArgumentProcessor_test;

    ArgumentProcessor();

    virtual ~ArgumentProcessor();

    void registerPositionalArgument(Argument* argument);

    void registerOptionalArgument(
        Argument*                              argument,
        const std::unordered_set<std::string>& flags);


    // Process a single argument
    void process(const std::string& argument);

    // Process multiple sequential arguments
    void process(const std::list<std::string>& arguments);

    // For arguments straight off the command line
    void process(int argc, char** argv);


    bool isSatisfied() const;

private:

    void checkForDuplicateFlag(const std::string& flag) const;

    std::list<Argument*> positional_arguments;

    // Tracks the positional argument we're going to process next
    std::list<Argument*>::iterator next_positional_argument;

    // Maps optional arguments that DO NOT themselves have values to their
    // representative objects. Multiple flags will link to the same object for
    // arguments with multiple flags (ex. -v and --verbose).
    std::unordered_map<std::string, Argument*> optional_arguments;

    // The optional value argument we're in the middle of processing
    std::unordered_map<std::string, Argument*>::iterator
    current_optional_argument;

    ArgumentProcessor(const ArgumentProcessor& argument_processor);
    ArgumentProcessor& operator=(const ArgumentProcessor& argument_processor);
};

#endif
