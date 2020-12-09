#if !defined CONFIGURATION_PARAMETER_TEMPLATE_BASE_HPP
#define CONFIGURATION_PARAMETER_TEMPLATE_BASE_HPP

#include <stdexcept>
#include <string>

#include "ConfigurationParameterBase.hpp"

namespace Configuration
{
    // Adds to ConfigurationParameterBase an actual definition of the "value" that is protected
    // by the "set" data member back up in ConfigurationParameterBase.  Any type can be used as
    // the value, as long as it's assignable.
    template <class T> class ParameterTemplateBase : public ParameterBase
    {
    public:

        friend class ParameterTemplateBase_test;

        explicit ParameterTemplateBase(const T& initial_value = T());
        ParameterTemplateBase(const ParameterTemplateBase& parameter);

        virtual ~ParameterTemplateBase();

        // Defines how to convert a ParameterTemplateBase<T> to a T
        operator T() const;

        void setValue(const T& value);

        // Returns the current value on the stack.  Try to use the other getValue() method if T
        // is large in memory.
        T getValue() const;

        // Returns a reference to the current value of the configuration parameter.
        void getValue(T& value) const;

        ParameterTemplateBase& operator=(const ParameterTemplateBase& parameter);
        ParameterTemplateBase& operator=(const T& parameter);

    protected:

        T value;
    };
}

#endif
