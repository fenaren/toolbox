#include "Argument.hpp"

//==============================================================================
Argument::Argument(const std::string& name,
                   const std::string& description) :
    name(name),
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
        std::string name;
        argument.getName(name);
        this->name = name;

        std::string description;
        argument.getDescription(description);
        this->description = description;

        satisfied = argument.isSatisfied();
    }

    return *this;
}
