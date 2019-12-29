#include <string>

#include "ArgumentValueCount.hpp"

//==============================================================================
ArgumentValueCount::ArgumentValueCount(unsigned int default_count) :
    Argument(),
    count(default_count)
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
    set();
}

//==============================================================================
ArgumentValueCount&
ArgumentValueCount::operator=(const ArgumentValueCount& argument_value_count)
{
    Argument::operator=(argument_value_count);

    // Don't do anything if we're assigning to ourselves
    if (this != &argument_value_count)
    {
        count = argument_value_count.count;
    }

    return *this;
}

//==============================================================================
ArgumentValueCount& ArgumentValueCount::operator=(unsigned int count)
{
    this->count = count;
    set();

    return *this;
}

//==============================================================================
bool operator<(const ArgumentValueCount& lhs, const ArgumentValueCount& rhs)
{
    return lhs.getCount() < rhs.getCount();
}

//==============================================================================
bool operator>(const ArgumentValueCount& lhs, const ArgumentValueCount& rhs)
{
    return rhs < lhs;
}

//==============================================================================
bool operator<=(const ArgumentValueCount& lhs, const ArgumentValueCount& rhs)
{
    return !(lhs > rhs);
}

//==============================================================================
bool operator>=(const ArgumentValueCount& lhs, const ArgumentValueCount& rhs)
{
    return !(lhs < rhs);
}

//==============================================================================
bool operator==(const ArgumentValueCount& lhs, const ArgumentValueCount& rhs)
{
    return lhs.getCount() == rhs.getCount();
}

//==============================================================================
bool operator!=(const ArgumentValueCount& lhs, const ArgumentValueCount& rhs)
{
    return !(lhs == rhs);
}
