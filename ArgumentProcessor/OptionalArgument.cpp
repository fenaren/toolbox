#include <string>

#include "OptionalArgument.hpp"

//==============================================================================
OptionalArgument::OptionalArgument(const std::string& name,
                                   const std::string& description) :
    Argument(name, description)
{
}

//==============================================================================
OptionalArgument::~OptionalArgument()
{
}

//==============================================================================
// If implemented, operator= should follow this template
//==============================================================================
OptionalArgument&
OptionalArgument::operator=(const OptionalArgument& template_class)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &template_class)
    {
        // Do something
    }

    return *this;
}
