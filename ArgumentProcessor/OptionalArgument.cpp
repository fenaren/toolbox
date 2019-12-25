#include <string>
#include <unordered_set>

#include "OptionalArgument.hpp"

#include "Argument.hpp"

//==============================================================================
OptionalArgument::OptionalArgument() :
    Argument(),
    set_count(0)
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
OptionalArgument&
OptionalArgument::operator=(const OptionalArgument& optional_argument)
{
    Argument::operator=(optional_argument);

    // Don't do anything if we're assigning to ourselves
    if (this != &optional_argument)
    {
        set_count = optional_argument.set_count;
    }

    return *this;
}
