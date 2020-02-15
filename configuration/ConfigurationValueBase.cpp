#include "ConfigurationValueBase.hpp"

//==============================================================================
ConfigurationValueBase::ConfigurationValueBase() :
    _set(false)
{
}

//==============================================================================
ConfigurationValueBase::ConfigurationValueBase(
    const ConfigurationValueBase& configuration_value_base)
{
    *this = configuration_value_base;
}

//==============================================================================
ConfigurationValueBase::~ConfigurationValueBase()
{
}

//==============================================================================
ConfigurationValueBase& ConfigurationValueBase::operator=(
    const ConfigurationValueBase& configuration_value_base)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &configuration_value_base)
    {
        _set = configuration_value_base._set;
    }

    return *this;
}
