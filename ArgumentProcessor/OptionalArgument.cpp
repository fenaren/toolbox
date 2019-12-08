#include <string>

#include "OptionalArgument.hpp"

//==============================================================================
OptionalArgument::OptionalArgument(const std::string& name,
                                   const std::string& description) :
    Argument(name, description),
    done_processing(false)
{
}

//==============================================================================
OptionalArgument::~OptionalArgument()
{
}

//==============================================================================
void OptionalArgument::process(const std::string& argument)
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
