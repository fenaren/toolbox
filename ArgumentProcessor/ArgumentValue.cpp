#include <sstream>
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
template <class T> T ArgumentValue::getValue() const
{
    std::istringstream converter(value);
    T value_tmp;
    converter >> value_tmp;
    return value_tmp;
}

//==============================================================================
template <class T> void ArgumentValue::getValue(T& value) const
{
    std::istringstream converter(this->value);
    converter >> value;
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

template void ArgumentValue::getValue(std::string&) const;

template void ArgumentValue::getValue(char&) const;
template void ArgumentValue::getValue(double&) const;
template void ArgumentValue::getValue(float&) const;
template void ArgumentValue::getValue(int&) const;
template void ArgumentValue::getValue(long&) const;
template void ArgumentValue::getValue(long double&) const;
template void ArgumentValue::getValue(long long&) const;
template void ArgumentValue::getValue(short&) const;
template void ArgumentValue::getValue(unsigned char&) const;
template void ArgumentValue::getValue(unsigned int&) const;
template void ArgumentValue::getValue(unsigned long&) const;
template void ArgumentValue::getValue(unsigned long long&) const;
template void ArgumentValue::getValue(unsigned short&) const;

template char               ArgumentValue::getValue() const;
template double             ArgumentValue::getValue() const;
template float              ArgumentValue::getValue() const;
template int                ArgumentValue::getValue() const;
template long               ArgumentValue::getValue() const;
template long double        ArgumentValue::getValue() const;
template long long          ArgumentValue::getValue() const;
template short              ArgumentValue::getValue() const;
template unsigned char      ArgumentValue::getValue() const;
template unsigned int       ArgumentValue::getValue() const;
template unsigned long      ArgumentValue::getValue() const;
template unsigned long long ArgumentValue::getValue() const;
template unsigned short     ArgumentValue::getValue() const;
