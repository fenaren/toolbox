#include <iterator>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include "ArgumentProcessor.hpp"

#include "OptionalArgument.hpp"
#include "PositionalArgument.hpp"

//==============================================================================
ArgumentProcessor::ArgumentProcessor() :
    current_pa(positional_arguments.end())
{
    // It's a safe bet users will always want the program name registered.
    // Positional arguments won't work correctly otherwise.
    registerName();
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
    positional_arguments.push_back(PositionalArgument(name, description));

    // If we just added the first positional argument then we have to start
    // processing positional arguments from here.  There's nowhere else to
    // process from.
    if (positional_arguments.size() == 1)
    {
        current_pa = positional_arguments.begin();
    }

    // The idea here is to support processing additional arguments after we've
    // already processed a set of existing ones.  Probably not a very likely use
    // case but it seems nice.
    if (current_pa == positional_arguments.end())
    {
        current_pa = std::prev(positional_arguments.end());
    }
}

//==============================================================================
void ArgumentProcessor::registerOptionalArgument(
        const std::string&                     name,
        const std::string&                     description,
        const std::unordered_set<std::string>& aliases)
{
}

//==============================================================================
void ArgumentProcessor::process(const std::string& argument)
{
    std::unordered_map<std::string, OptionalArgument>::iterator found_opt_arg =
        optional_arguments.find(argument);

    // Is this argument one of the optional arguments?
    if (found_opt_arg != optional_arguments.end())
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
// If implemented, operator= should follow this template
//==============================================================================
ArgumentProcessor&
ArgumentProcessor::operator=(const ArgumentProcessor& template_class)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &template_class)
    {
        // Do something
    }

    return *this;
}
