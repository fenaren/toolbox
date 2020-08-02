#if !defined CONFIGURATION_SIMPLE_PARAMETER_HPP
#define CONFIGURATION_SIMPLE_PARAMETER_HPP

#include <list>
#include <string>

#include "ConfigurationParameter.hpp"

namespace Configuration
{
    template <class T> class SimpleParameter : public Parameter<T>
    {
    public:

        explicit SimpleParameter(const T& initial_value = T());

        // Defrobnicates the widget.  Make this virtual if this class derives from something
        virtual ~SimpleParameter();

        virtual void fromString(const std::string& value);
        virtual void toString(std::string& value) const;
    };
}

#endif
