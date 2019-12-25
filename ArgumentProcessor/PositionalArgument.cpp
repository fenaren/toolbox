#include <sstream>
#include <string>

#include "PositionalArgument.hpp"

#include "Argument.hpp"

//==============================================================================
PositionalArgument::PositionalArgument() :
    Argument(),
    set(false)
{
}

//==============================================================================
PositionalArgument::PositionalArgument(
    const PositionalArgument& positional_argument) :
    Argument(positional_argument)
{
    *this = positional_argument;
}

//==============================================================================
PositionalArgument::~PositionalArgument()
{
}

//==============================================================================
template <class T> T PositionalArgument::getValue() const
{
    std::istringstream converter(value);
    T value_tmp;
    converter >> value_tmp;
    return value_tmp;
}

//==============================================================================
PositionalArgument&
PositionalArgument::operator=(const PositionalArgument& positional_argument)
{
    Argument::operator=(positional_argument);

    // Don't do anything if we're assigning to ourselves
    if (this != &positional_argument)
    {
        value = positional_argument.value;
        set   = positional_argument.set;
    }

    return *this;
}
