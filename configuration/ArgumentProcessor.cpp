#include <iterator>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "ArgumentProcessor.hpp"

#include "ConfigurationValue.hpp"

//==============================================================================
ArgumentProcessor::ArgumentProcessor() :
    next_positional_argument(positional_arguments.end()),
    current_optional_argument(optional_arguments.end())
{
}

//==============================================================================
ArgumentProcessor::~ArgumentProcessor()
{
}

//==============================================================================
template <class T> void
ArgumentProcessor::registerPositionalArgument(ConfigurationValue<T>* argument)
{
    positional_arguments.push_back(argument);

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
    ConfigurationValue*                              argument,
    const std::unordered_set<std::string>& flags)
{
    // Don't bother if no flags were provided
    if (flags.empty())
    {
        throw std::invalid_argument(
            "Argument \"flags\" must specify at least one flag");
    }

    // Index by flags
    for (std::unordered_set<std::string>::const_iterator flag = flags.begin();
         flag != flags.end();
         ++flag)
    {
        // Do not allow multiple optional arguments to share flags.  That
        // wouldn't make any sense.
        if (optional_arguments.find(*flag) != optional_arguments.end())
        {
            throw std::runtime_error("Optional argument with flag \"" + *flag +
                                     "\" already registered");
        }

        optional_arguments[*flag] = argument;
    }
}

//==============================================================================
void ArgumentProcessor::process(const std::string& argument)
{
    // Are we looking for a value for an optional argument?
    if (current_optional_argument != optional_arguments.end())
    {
        // Update whatever argument we're working with the new value
        current_optional_argument->second->update(argument);

        // Note that we're done processing this optional argument
        current_optional_argument = optional_arguments.end();

        // We've done all we should with this argument.
        return;
    }

    // If we're here then we're not processing the value for an optional
    // argument.

    // Have we been given a flag for an optional argument?
    current_optional_argument = optional_arguments.find(argument);

    if (current_optional_argument != optional_arguments.end())
    {
        if (dynamic_cast<ConfigurationValueCount*>(
                current_optional_argument->second))
        {
            current_optional_argument->second->update();
            current_optional_argument = optional_arguments.end();
        }

        return;
    }

    // By this point we know this argument must be positional.  There's no other
    // possibility.

    if (next_positional_argument != positional_arguments.end())
    {
        (*next_positional_argument)->update(argument);
        ++next_positional_argument;
    }
    else
    {
        // All positional arguments have been processed already, so this is an
        // extra argument that belongs nowhere.
        throw std::runtime_error("Extra positional argument");
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
bool ArgumentProcessor::isSatisfied() const
{
    return next_positional_argument == positional_arguments.end() &&
        current_optional_argument == optional_arguments.end();
}

template void ArgumentProcessor::registerPositionalArgument(
    ConfigurationValue<std::string>*);

template void ArgumentProcessor::registerPositionalArgument(
    ConfigurationValue<char>*);

template void ArgumentProcessor::registerPositionalArgument(
    ConfigurationValue<double>*);

template void ArgumentProcessor::registerPositionalArgument(
    ConfigurationValue<float>*);

template void ArgumentProcessor::registerPositionalArgument(
    ConfigurationValue<int>*);

template void ArgumentProcessor::registerPositionalArgument(
    ConfigurationValue<long>*);

template void ArgumentProcessor::registerPositionalArgument(
    ConfigurationValue<long double>*);

template void ArgumentProcessor::registerPositionalArgument(
    ConfigurationValue<long long>*);

template void ArgumentProcessor::registerPositionalArgument(
    ConfigurationValue<short>*);

template void ArgumentProcessor::registerPositionalArgument(
    ConfigurationValue<unsigned char>*);

template void ArgumentProcessor::registerPositionalArgument(
    ConfigurationValue<unsigned int>*);

template void ArgumentProcessor::registerPositionalArgument(
    ConfigurationValue<unsigned long>*);

template void ArgumentProcessor::registerPositionalArgument(
    ConfigurationValue<unsigned long long>*);

template void ArgumentProcessor::registerPositionalArgument(
    ConfigurationValue<unsigned short>*);
