#include "ConfigurationParameterBase.hpp"

namespace Configuration
{

//==============================================================================
    ParameterBase::ParameterBase() :
        _set(false)
    {
    }

//==============================================================================
    ParameterBase::ParameterBase(const ParameterBase& parameter_base)
    {
        *this = parameter_base;
    }

//==============================================================================
    ParameterBase::~ParameterBase()
    {
    }

//==============================================================================
    ParameterBase&
    ParameterBase::operator=(const ParameterBase& parameter_base)
    {
        // Don't do anything if we're assigning to ourselves
        if (this != &parameter_base)
        {
            _set = parameter_base._set;
        }

        return *this;
    }

}
