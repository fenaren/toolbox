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
        std::string name;
        argument.getName(name);
        this->name = name;
    }

    return *this;
}
