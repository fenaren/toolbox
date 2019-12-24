#include <string>

#include "Argument.hpp"

//==============================================================================
Argument::Argument(const std::string& name) :
    name(name)
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
        name = argument.name;
    }

    return *this;
}
