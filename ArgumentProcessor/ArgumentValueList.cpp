#include "ArgumentValueList.hpp"

//==============================================================================
ArgumentValueList::ArgumentValueList()
{
}

//==============================================================================
ArgumentValueList::~ArgumentValueList()
{
}

//==============================================================================
void ArgumentValueList::update(const std::string& value)
{
    values.push_back(value);
    set();
}

//==============================================================================
ArgumentValueList& ArgumentValueList::operator=(
    const ArgumentValueList& argument_value_list)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &argument_value_list)
    {
        // Do something
    }

    return *this;
}
