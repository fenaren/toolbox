#include <iterator>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "ConfigurationArgumentProcessor.hpp"

#include "ConfigurationParameter.hpp"

//=============================================================================================
Configuration::ArgumentProcessor::ArgumentProcessor() :
    next_positional_argument(positional_arguments.end()),
    current_optional_argument(optional_arguments.end())
{
}

//=============================================================================================
Configuration::ArgumentProcessor::~ArgumentProcessor()
{
}

//=============================================================================================
void Configuration::ArgumentProcessor::registerPositionalArgument(ParameterBase* argument)
{
    // Don't let the user register over top of something already registered.
    if (isRegistered(argument))
    {
        throw std::runtime_error("Parameter already registered");
    }

    positional_arguments.push_back(argument);

    // If we just added the first positional argument then we have to start processing
    // positional arguments from here.  There's nowhere else to process from.
    if (positional_arguments.size() == 1)
    {
        next_positional_argument = positional_arguments.begin();
    }

    // The idea here is to support processing additional arguments after we've already
    // processed a set of existing ones.  Probably not a very likely use case but it seems
    // nice.
    if (next_positional_argument == positional_arguments.end())
    {
        next_positional_argument = std::prev(positional_arguments.end());
    }
}

//=============================================================================================
void Configuration::ArgumentProcessor::registerOptionalArgument(
    ParameterBase*                         argument,
    const std::unordered_set<std::string>& flags)
{
    // Don't bother if no flags were provided
    if (flags.empty())
    {
        throw std::invalid_argument("Argument \"flags\" must specify at least one flag");
    }

    // Don't let the user register over top of something already registered.
    if (isRegistered(argument))
    {
        throw std::runtime_error("Parameter already registered");
    }

    // Index by flags
    for (std::unordered_set<std::string>::const_iterator flag = flags.begin();
         flag != flags.end();
         ++flag)
    {
        // Do not allow multiple optional arguments to share flags.  That wouldn't make any
        // sense.
        if (optional_arguments.find(*flag) != optional_arguments.end())
        {
            throw std::runtime_error("Optional argument with flag \"" + *flag +
                                     "\" already registered");
        }

        optional_arguments[*flag] = argument;
    }
}

//=============================================================================================
void Configuration::ArgumentProcessor::registerOptionalCountingArgument(
    Parameter<unsigned int>*               argument,
    const std::unordered_set<std::string>& flags)
{
    // Don't bother if no flags were provided
    if (flags.empty())
    {
        throw std::invalid_argument("Argument \"flags\" must specify at least one flag");
    }

    // Don't let the user register over top of something already registered.
    if (isRegistered(argument))
    {
        throw std::runtime_error("Parameter already registered");
    }

    // Index by flags
    for (std::unordered_set<std::string>::const_iterator flag = flags.begin();
         flag != flags.end();
         ++flag)
    {
        // Do not allow multiple optional arguments to share flags.  That wouldn't make any
        // sense.
        if (optional_counting_arguments.find(*flag) != optional_counting_arguments.end())
        {
            throw std::runtime_error("Optional argument with flag \"" + *flag +
                                     "\" already registered");
        }

        optional_counting_arguments[*flag] = argument;
    }
}

//=============================================================================================
void Configuration::ArgumentProcessor::process(const std::string& argument)
{
    // Are we looking for a value for an optional argument?
    if (current_optional_argument != optional_arguments.end())
    {
        // Update whatever argument we're working with the new value
        current_optional_argument->second->setValue(argument);

        // Note that we're done processing this optional argument
        current_optional_argument = optional_arguments.end();

        // We've done all we should with this argument.
        return;
    }

    // If we're here then we're not processing the value for an optional argument.

    // Have we been given a flag for an optional argument that doesn't take a value?
    std::unordered_map<std::string, Parameter<unsigned int>*>::iterator i =
        optional_counting_arguments.find(argument);
    if (i != optional_counting_arguments.end())
    {
        *(i->second) = i->second->getValue() + 1;
        return;
    }

    // Have we been given a flag for an optional argument that does take a value?
    current_optional_argument = optional_arguments.find(argument);
    if (current_optional_argument != optional_arguments.end())
    {
        return;
    }

    // By this point we know this argument must be positional.  There's no other possibility.

    if (next_positional_argument != positional_arguments.end())
    {
        (*next_positional_argument)->setValue(argument);
        ++next_positional_argument;
        return;
    }

    // All positional arguments have been processed already, so this is an extra argument that
    // belongs nowhere.
    throw std::runtime_error("Extra positional argument");
}

//=============================================================================================
void Configuration::ArgumentProcessor::process(const std::list<std::string>& arguments)
{
    for (std::list<std::string>::const_iterator i = arguments.begin();
         i != arguments.end();
         ++i)
    {
        process(*i);
    }
}

//=============================================================================================
void Configuration::ArgumentProcessor::process(int argc, char** argv)
{
    for (int i = 0; i < argc; ++i)
    {
        process(argv[i]);
    }
}

//=============================================================================================
bool Configuration::ArgumentProcessor::isRegistered(const ParameterBase* cv) const
{
    for (std::list<ParameterBase*>::const_iterator i = positional_arguments.begin();
         i != positional_arguments.end();
         ++i)
    {
        if (*i == cv)
        {
            return true;
        }
    }

    for (std::unordered_map<std::string, ParameterBase*>::const_iterator i =
             optional_arguments.begin();
         i != optional_arguments.end();
         ++i)
    {
        if (i->second == cv)
        {
            return true;
        }
    }

    for (std::unordered_map<std::string, Parameter<unsigned int>*>::const_iterator i =
             optional_counting_arguments.begin();
         i != optional_counting_arguments.end();
         ++i)
    {
        if (i->second == cv)
        {
            return true;
        }
    }

    return false;
}
