#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "ArgumentProcessor.hpp"

#include "OptionalArgument.hpp"
#include "PositionalArgument.hpp"

//==============================================================================
ArgumentProcessor::ArgumentProcessor() :
    next_positional_argument(positional_arguments.end()),
    current_optional_argument(optional_arguments.end())
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
/*void ArgumentProcessor::registerOptionalArgument(
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

    std::shared_ptr<OptionalArgument> optional_argument(
        new OptionalArgument(name, has_a_value));

    // Map all the flags to the ArgumentProcessor we've configured to handle
    // them.
    for (std::unordered_set<std::string>::const_iterator i = flags.begin();
         i != flags.end();
         ++i)
    {
        // Do not allow multiple optional arguments to share flags
        if (optional_arguments.find(*i) != optional_arguments.end())
        {
            throw std::runtime_error(
                "Optional argument with flag " + *i + " already registered");
        }

        optional_arguments[*i] = optional_argument;
    }
    }*/

//==============================================================================
void ArgumentProcessor::reset()
{
    positional_arguments.clear();
    optional_arguments.clear();

    next_positional_argument  = positional_arguments.end();
    current_optional_argument = optional_arguments.end();
}

//==============================================================================
bool ArgumentProcessor::isSpecified() const
{
    // Doesn't consider optional arguments because they're optional
    return next_positional_argument == positional_arguments.end();
}

//==============================================================================
void ArgumentProcessor::process(const std::string& argument)
{
    // There is a two-dimensional state machine here, represented by the
    // next_positional_argument and current_optional_argument iterator class
    // members.

    // If we're not already processing an optional argument, try to find one
    // that matches the current argument.
    if (current_optional_argument == optional_arguments.end())
    {
        current_optional_argument = optional_arguments.find(argument);

        if (current_optional_argument != optional_arguments.end())
        {
            // We just found a new optional argument to process.
            return;
        }
    }

    // Are we processing an optional argument?  This if can be true multiple
    // times for the same value of the current_optional_argument iterator.  This
    // will happen for all optional arguments that themselves take arguments.
    if (current_optional_argument != optional_arguments.end())
    {
        //current_optional_argument->second->process(argument);

        // Stop processing this optional argument only when it says it's done.
        //if (current_optional_argument->second->isSpecified())
        //{
        //    current_optional_argument = optional_arguments.end();
        //}
    }
    else
    {
        // It's not optional, so process it as a positional argument.
        next_positional_argument->specifyValue(argument);

        // We're ready for the next positional argument.
        ++next_positional_argument;
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
