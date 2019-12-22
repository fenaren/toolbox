#include <string>

#include "PositionalArgument.hpp"

#include "Argument.hpp"

//==============================================================================
PositionalArgument::PositionalArgument(const std::string& name,
                                       const std::string& description) :
    Argument(name, description)
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
    // Don't do anything if we're assigning to ourselves
    if (this != &positional_argument)
    {
        Argument::operator=(positional_argument);

        std::string value;
        positional_argument.getValue(value);

        this->value     = value;
        this->specified = positional_argument.isSpecified();
    }

    return *this;
}
