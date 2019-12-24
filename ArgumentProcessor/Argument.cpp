#include <string>

#include "Argument.hpp"

//==============================================================================
Argument::Argument()
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
        // TBD
    }

    return *this;
}
