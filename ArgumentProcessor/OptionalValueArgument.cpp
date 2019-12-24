#include "OptionalValueArgument.hpp"

//==============================================================================
OptionalValueArgument::OptionalValueArgument() :
    OptionalArgument()
{
}

//==============================================================================
OptionalValueArgument::~OptionalValueArgument()
{
}

//==============================================================================
OptionalValueArgument& OptionalValueArgument::operator=(
    const OptionalValueArgument& optional_value_argument)
{
    OptionalArgument::operator=(optional_value_argument);

    // Don't do anything if we're assigning to ourselves
    if (this != &optional_value_argument)
    {
        // Do something
    }

    return *this;
}
