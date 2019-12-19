#include "Argument.hpp"

//==============================================================================
Argument::Argument(const std::string& description) :
    description(description),
    satisfied(false)
{
}

//==============================================================================
Argument::Argument(const Argument& argument)
{
    *this = argument;
}

//==============================================================================
Argument::~Argument()
{
}

//==============================================================================
Argument& Argument::operator=(const Argument& argument)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &argument)
    {
        std::string description;
        argument.getDescription(description);
        this->description = description;

        satisfied = argument.isSatisfied();
    }

    return *this;
}
