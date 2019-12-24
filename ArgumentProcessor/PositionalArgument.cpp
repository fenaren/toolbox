#include <string>

#include "PositionalArgument.hpp"

#include "Argument.hpp"

//==============================================================================
PositionalArgument::PositionalArgument(const std::string& name) :
    Argument(name)
{
}

//==============================================================================
PositionalArgument::PositionalArgument(
    const PositionalArgument& positional_argument) :
    Argument(positional_argument)
{
    *this = positional_argument;
}

//==============================================================================
PositionalArgument::~PositionalArgument()
{
}

//==============================================================================
PositionalArgument&
PositionalArgument::operator=(const PositionalArgument& positional_argument)
{
    Argument::operator=(positional_argument);

    // Don't do anything if we're assigning to ourselves
    if (this != &positional_argument)
    {
        value     = positional_argument.value;
        specified = positional_argument.specified;
    }

    return *this;
}
