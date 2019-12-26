#include <string>

#include "ArgumentValue.hpp"

#include "Argument.hpp"

//==============================================================================
ArgumentValue::ArgumentValue() :
    Argument()
{
}

//==============================================================================
ArgumentValue::~ArgumentValue()
{
}

//==============================================================================
void ArgumentValue::update(const std::string& value)
{
    this->value = value;
    set();
}

//==============================================================================
ArgumentValue& ArgumentValue::operator=(const ArgumentValue& argument_value)
{
    Argument::operator=(argument_value);

    // Don't do anything if we're assigning to ourselves
    if (this != &argument_value)
    {
        value = argument_value.value;
    }

    return *this;
}
