#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "ArgumentProcessor.hpp"

#include "OptionalArgument.hpp"
#include "OptionalValueArgument.hpp"
#include "PositionalArgument.hpp"

//==============================================================================
ArgumentProcessor::ArgumentProcessor() :
    next_positional_argument(positional_arguments.end()),
    current_optional_value_argument(optional_value_arguments.end())
{
}

//==============================================================================
ArgumentProcessor::ArgumentProcessor(
    const ArgumentProcessor& argument_processor)
{
    *this = argument_processor;
}

//==============================================================================
ArgumentProcessor::~ArgumentProcessor()
{
}

//==============================================================================
void ArgumentProcessor::registerPositionalArgument(
    const std::string& name,
    const std::string& description)
{
    positional_arguments.push_back(PositionalArgument(name));

    // If we just added the first positional argument then we have to start
    // processing positional arguments from here.  There's nowhere else to
    // process from.
    if (positional_arguments.size() == 1)
    {
        next_positional_argument = positional_arguments.begin();
    }

    // The idea here is to support processing additional arguments after we've
    // already processed a set of existing ones.  Probably not a very likely use
    // case but it seems nice.
    if (next_positional_argument == positional_arguments.end())
    {
        next_positional_argument = std::prev(positional_arguments.end());
    }
}

//==============================================================================
void ArgumentProcessor::registerOptionalArgument(
    const std::string&                     name,
    const std::string&                     description,
    const std::unordered_set<std::string>& flags,
    bool                                   has_a_value)
{
    // Don't bother if no flags were provided
    if (flags.empty())
    {
        throw std::invalid_argument(
            "Argument \"flags\" must contain at least one flag");
    }

    if (has_a_value)
    {
        std::shared_ptr<OptionalValueArgument> optional_value_argument(
            new OptionalValueArgument(name));

        // Map all the flags to the new OptionalValueArgment
        for (std::unordered_set<std::string>::const_iterator i = flags.begin();
             i != flags.end();
             ++i)
        {
            // Do not allow multiple optional arguments (either
            // OptionalArguments or OptionalValueArguments) to share flags
            if (optional_arguments.find(*i) != optional_arguments.end() ||
                optional_value_arguments.find(*i) !=
                optional_value_arguments.end())
            {
                throw std::runtime_error(
                    "Optional argument with flag " + *i +
                    " already registered");
            }

            optional_value_arguments[*i] = optional_value_argument;
        }
    }
    else
    {
        std::shared_ptr<OptionalArgument> optional_argument(
            new OptionalArgument(name));

        // Map all the flags to the new OptionalArgment
        for (std::unordered_set<std::string>::const_iterator i = flags.begin();
             i != flags.end();
             ++i)
        {
            // Do not allow multiple optional arguments to share flags
            if (optional_arguments.find(*i) != optional_arguments.end() ||
                optional_value_arguments.find(*i) !=
                optional_value_arguments.end())
            {
                throw std::runtime_error(
                    "Optional argument with flag " + *i +
                    " already registered");
            }

            optional_arguments[*i] = optional_argument;
        }
    }

}

//==============================================================================
void ArgumentProcessor::process(const std::string& argument)
{
    // Are we in the middle of processing an optional argument that takes a
    // value?
    if (current_optional_value_argument != optional_value_arguments.end())
    {
        // Specify the value
        current_optional_value_argument->second->specify(argument);

        // Note that we're no longer processing this optional value argument
        current_optional_value_argument = optional_value_arguments.end();

        // We've done all we should with this argument.
        return;
    }

    // If we're here then we're not processing the value for an optional
    // argument that takes a value.

    // Have we been given a flag for an optional argument that takes a value?
    current_optional_value_argument = optional_value_arguments.find(argument);

    if (current_optional_value_argument != optional_value_arguments.end())
    {
        // We've seen a flag for an optional argument that takes a value.  Now
        // we must wait for the value to come in the next argument.
        return;
    }

    // If we're here we're either processing an optional argument that doesn't
    // take a value, or we're processing a positional argument.

    // Are we processing an optional argument?
    OptionalArgumentsMap::const_iterator i = optional_arguments.find(argument);
    if (i != optional_arguments.end())
    {
        // Note that the argument is specified.
        i->second->specify();

        // We've done all we should with this argument.
        return;
    }

    // By this point we know this argument must be positional.  There's no other
    // possibility.

    if (next_positional_argument != positional_arguments.end())
    {
        next_positional_argument->specifyValue(argument);
        ++next_positional_argument;
    }
    else
    {
    }
}

//==============================================================================
void ArgumentProcessor::process(const std::list<std::string>& arguments)
{
    for (std::list<std::string>::const_iterator i = arguments.begin();
         i != arguments.end();
         ++i)
    {
        process(*i);
    }
}

//==============================================================================
void ArgumentProcessor::process(int argc, char** argv)
{
    for (int i = 0; i < argc; ++i)
    {
        process(argv[i]);
    }
}

//==============================================================================
ArgumentProcessor& ArgumentProcessor::operator=(
    const ArgumentProcessor& argument_processor)
{
    if (this != &argument_processor)
    {
        positional_arguments = argument_processor.positional_arguments;
        optional_arguments   = argument_processor.optional_arguments;

        // Mirror the iterators
    }

    return *this;
}
