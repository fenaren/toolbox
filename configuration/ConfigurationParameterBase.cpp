#include "ConfigurationParameterBase.hpp"

namespace Configuration
{
    ParameterBase::ParameterBase() :
        set(false)
    {
    }

    ParameterBase::ParameterBase(const ParameterBase& parameter_base) :
        set(false)
    {
    }

    ParameterBase::~ParameterBase()
    {
    }
}
