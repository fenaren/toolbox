#include <string>

#include "PositionalArgument.hpp"

//==============================================================================
PositionalArgument::PositionalArgument(const std::string& name,
                                       const std::string& description) :
    Argument(name, description)
{
}

//==============================================================================
PositionalArgument::~PositionalArgument()
{
}

//==============================================================================
void PositionalArgument::process(const std::string& argument)
{
    setValue(argument);
}

//==============================================================================
PositionalArgument&
PositionalArgument::operator=(const PositionalArgument& template_class)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &template_class)
    {
        // Do something
    }

    return *this;
}
