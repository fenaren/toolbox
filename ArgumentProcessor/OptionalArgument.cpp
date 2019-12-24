#include <string>
#include <unordered_set>

#include "OptionalArgument.hpp"

#include "Argument.hpp"

//==============================================================================
OptionalArgument::OptionalArgument(const std::string& name) :
    Argument(name)
{
}

//==============================================================================
OptionalArgument::OptionalArgument(const OptionalArgument& optional_argument) :
    Argument()
{
    *this = optional_argument;
}

//==============================================================================
OptionalArgument::~OptionalArgument()
{
}

//==============================================================================
bool OptionalArgument::isSpecified() const
{
    return false;
}

//==============================================================================
void OptionalArgument::reset()
{
}

//==============================================================================
OptionalArgument&
OptionalArgument::operator=(const OptionalArgument& optional_argument)
{
    Argument::operator=(optional_argument);

    // Don't do anything if we're assigning to ourselves
    if (this != &optional_argument)
    {
        values = optional_argument.values;
    }

    return *this;
}
