#include <sstream>
#include <string>

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
template <class T> T OptionalValueArgument::getLastValue() const
{
    std::istringstream converter(values.back());
    T value_tmp;
    converter >> value_tmp;
    return value_tmp;
}

//==============================================================================
template <class T>
void OptionalValueArgument::getValues(std::list<T>& values) const
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
