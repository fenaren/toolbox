#include <string>

#include "PositionalArgumentList.hpp"

//==============================================================================
PositionalArgumentList::PositionalArgumentList(const std::string& description) :
    PositionalArgument(description)
{
}

//==============================================================================
PositionalArgumentList::~PositionalArgumentList()
{
}

//==============================================================================
PositionalArgumentList& PositionalArgumentList::operator=(
    const PositionalArgumentList& positional_argument_list)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &positional_argument_list)
    {
        // Do something
    }

    return *this;
}
