#include "Argument.hpp"

//==============================================================================
Argument::Argument(const std::string& name,
                   const std::string& description) :
    name(name),
    description(description),
    satisfied(false)
{
}

//==============================================================================
Argument::Argument(const Argument& argument)
{
    *this = argument;
}

//==============================================================================
Argument::~Argument()
{
}

//==============================================================================
// If implemented, operator= should follow this template
//==============================================================================
Argument& Argument::operator=(const Argument& template_class)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &template_class)
    {
        // Do something
    }

    return *this;
}
