#include <string>

#include "PositionalArgument.hpp"

//==============================================================================
PositionalArgument::PositionalArgument(const std::string& description) :
    Argument(description)
{
}

//==============================================================================
PositionalArgument::PositionalArgument(
    const PositionalArgument& positional_argument)
{
    *this = positional_argument;
}

//==============================================================================
PositionalArgument::~PositionalArgument()
{
}

//==============================================================================
void PositionalArgument::process(const std::string& argument)
{
    value = argument;
    setSatisfied(true);
}

//==============================================================================
PositionalArgument&
PositionalArgument::operator=(const PositionalArgument& positional_argument)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &positional_argument)
    {
        std::string value;
        positional_argument.getValue(value);

        this->value = value;
    }

    return *this;
}
