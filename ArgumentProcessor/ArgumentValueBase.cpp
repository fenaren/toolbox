#include "ArgumentValueBase.hpp"

//==============================================================================
ArgumentValueBase::ArgumentValueBase() :
    value_set(false)
{
}

//==============================================================================
ArgumentValueBase::~ArgumentValueBase()
{
}

//==============================================================================
ArgumentValueBase&
ArgumentValueBase::operator=(const ArgumentValueBase& argument_value_base)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &argument_value_base)
    {
        value_set = argument_value_base.value_set;
    }

    return *this;
}
