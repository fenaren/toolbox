#include "Argument.hpp"

//==============================================================================
Argument::Argument() :
    _set(false)
{
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
        _set = argument._set;
    }

    return *this;
}
