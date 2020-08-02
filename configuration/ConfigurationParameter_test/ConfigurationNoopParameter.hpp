#if !defined CONFIGURATION_NOOP_PARAMETER_HPP
#define CONFIGURATION_NOOP_PARAMETER_HPP

#include <string>

#include "ConfigurationParameter.hpp"

namespace Configuration
{
    template <class T> class NoopParameter : public Parameter<T>
    {
    public:

        // Frobnicates the widget
        NoopParameter(const T& initial_value = T());

        // Defrobnicates the widget.  Make this virtual if this class derives from something
        virtual ~NoopParameter();

        virtual void fromString(const std::string& value);
        virtual void toString(std::string& value) const;

    private:

        // Copy construction and assignment not allowed.  Consider getting rid of the operator=
        // code in the implementation file if operator= remains private
        NoopParameter(const NoopParameter&);
        NoopParameter& operator=(const NoopParameter&);
    };
}

#endif
