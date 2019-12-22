#include <string>

#include "Argument.hpp"

//==============================================================================
Argument::Argument(const std::string& name,
                   const std::string& description) :
    name(name),
    description(description)
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
    if (this != &argument)
    {
        std::string name;
        argument.getName(name);
        this->name = name;

        std::string description;
        argument.getDescription(description);
        this->description = description;
    }

    return *this;
}
