#include "ArgumentValueCount.hpp"

//==============================================================================
ArgumentValueCount::ArgumentValueCount() :
    count(0)
{
}

//==============================================================================
ArgumentValueCount::~ArgumentValueCount()
{
}

//==============================================================================
void ArgumentValueCount::update(const std::string& value)
{
    // value argument intentionally ignored
    count++;
}

//==============================================================================
ArgumentValueCount&
ArgumentValueCount::operator=(const ArgumentValueCount& argument_value_count)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &argument_value_count)
    {
        count = argument_value_count.count;
    }

    return *this;
}
