#include <string>
#include <unordered_set>
#include <unordered_map>

#include "ArgumentProcessor.hpp"

#include "OptionalArgument.hpp"
#include "PositionalArgument.hpp"

//==============================================================================
ArgumentProcessor::ArgumentProcessor()
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
