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
    next_positional_argument(positional_arguments_list.end()),
    current_optional_value_argument(optional_value_arguments_flagmap.end())
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
void ArgumentProcessor::registerPositionalArgument(const std::string& name)
{
    // Ensure we haven't already registered an argument that uses this name.
    checkNamemapsForDuplicate(name);

    std::shared_ptr<PositionalArgument> positional_argument(
        new PositionalArgument());

    // Index this in the name map so we can quickly retrieve the value later.
    positional_arguments_namemap[name] = positional_argument;

    // If we just added the first positional argument then we have to start
    // processing positional arguments from here.  There's nowhere else to
    // process from.
    if (positional_arguments_list.size() == 1)
    {
        next_positional_argument = positional_arguments_list.begin();
    }

    // The idea here is to support processing additional arguments after we've
    // already processed a set of existing ones.  Probably not a very likely use
    // case but it seems nice.
    if (next_positional_argument == positional_arguments_list.end())
    {
        next_positional_argument = std::prev(positional_arguments_list.end());
    }
}

//==============================================================================
void ArgumentProcessor::registerOptionalArgument(
    const std::string&                     name,
    const std::unordered_set<std::string>& flags,
    bool                                   has_a_value)
{
    // Ensure we haven't already registered an argument that uses this name.
    checkNamemapsForDuplicate(name);

    // Don't bother if no flags were provided
    if (flags.empty())
    {
        throw std::invalid_argument(
            "Argument \"flags\" must contain at least one flag");
    }

    if (has_a_value)
    {
        std::shared_ptr<OptionalValueArgument> optional_value_argument(
            new OptionalValueArgument());

        // Index by name.  By this point we've made sure name is not already
        // registered to another argument.
        optional_value_arguments_namemap[name] = optional_value_argument;

        // Index by flags
        for (std::unordered_set<std::string>::const_iterator flag =
                 flags.begin();
             flag != flags.end();
             ++flag)
        {
            // Do not allow multiple optional arguments (either
            // OptionalArguments or OptionalValueArguments) to share flags
            checkFlagmapsForDuplicate(*flag);

            optional_value_arguments_flagmap[*flag] = optional_value_argument;
        }
    }
    else
    {
        std::shared_ptr<OptionalArgument> optional_argument(
            new OptionalArgument());

        // Index by name.  By this point we've made sure name is not already
        // registered to another argument.
        optional_arguments_namemap[name] = optional_argument;

        // Index by flags
        for (std::unordered_set<std::string>::const_iterator flag =
                 flags.begin();
             flag != flags.end();
             ++flag)
        {
            // Do not allow multiple optional arguments (either
            // OptionalArguments or OptionalValueArguments) to share flags
            checkFlagmapsForDuplicate(*flag);

            optional_arguments_flagmap[*flag] = optional_argument;
        }
    }

}

//==============================================================================
void ArgumentProcessor::process(const std::string& argument)
{
    // Are we in the middle of processing an optional argument that takes a
    // value?
    if (current_optional_value_argument !=
        optional_value_arguments_flagmap.end())
    {
        // Set the value
        current_optional_value_argument->second->setValue(argument);

        // Note that we're no longer processing this optional value argument
        current_optional_value_argument =
            optional_value_arguments_flagmap.end();

        // We've done all we should with this argument.
        return;
    }

    // If we're here then we're not processing the value for an optional
    // argument that takes a value.

    // Have we been given a flag for an optional argument that takes a value?
    current_optional_value_argument =
        optional_value_arguments_flagmap.find(argument);

    if (current_optional_value_argument !=
        optional_value_arguments_flagmap.end())
    {
        // We've seen a flag for an optional argument that takes a value.  Now
        // we must wait for the value to come in the next argument.
        return;
    }

    // If we're here we're either processing an optional argument that doesn't
    // take a value, or we're processing a positional argument.

    // Are we processing an optional argument?
    OptionalArgumentsMap::const_iterator i =
        optional_arguments_flagmap.find(argument);
    if (i != optional_arguments_flagmap.end())
    {
        // Note that the argument is set.
        i->second->set();

        // We've done all we should with this argument.
        return;
    }

    // By this point we know this argument must be positional.  There's no other
    // possibility.

    if (next_positional_argument != positional_arguments_list.end())
    {
        (*next_positional_argument)->setValue(argument);
        ++next_positional_argument;
    }
    else
    {
        // TODO
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
void ArgumentProcessor::checkNamemapsForDuplicate(const std::string& name) const
{
    if (positional_arguments_namemap.find(name) !=
        positional_arguments_namemap.end() ||
        optional_arguments_namemap.find(name) !=
        optional_arguments_namemap.end() ||
        optional_value_arguments_namemap.find(name) !=
        optional_value_arguments_namemap.end())
    {
        throw std::runtime_error("Argument with name \"" + name + "\" " +
                                 "already registered");
    }
}

//==============================================================================
void
ArgumentProcessor::checkFlagmapsForDuplicate(const std::string& flag) const
{
    if (optional_arguments_flagmap.find(flag) !=
        optional_arguments_flagmap.end() ||
        optional_value_arguments_flagmap.find(flag) !=
        optional_value_arguments_flagmap.end())
    {
        throw std::runtime_error("Optional argument with flag \"" + flag +
                                 "\" already registered");
    }
}

//==============================================================================
ArgumentProcessor& ArgumentProcessor::operator=(
    const ArgumentProcessor& argument_processor)
{
    if (this != &argument_processor)
    {
        positional_arguments_list =
            argument_processor.positional_arguments_list;

        optional_arguments_flagmap =
            argument_processor.optional_arguments_flagmap;

        optional_value_arguments_flagmap =
            argument_processor.optional_value_arguments_flagmap;

        // Mirror the iterators
    }

    return *this;
}
