#include <string>
#include <unordered_set>

#include "OptionalArgument.hpp"

#include "Argument.hpp"

//==============================================================================
OptionalArgument::OptionalArgument(const std::string& description) :
    Argument(description)
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
void OptionalArgument::process(const std::string& argument)
{
}

//==============================================================================
OptionalArgument&
OptionalArgument::operator=(const OptionalArgument& optional_argument)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &optional_argument)
    {
        std::string description;
        optional_argument.getDescription(description);
        setDescription(description);
    }

    return *this;
}
