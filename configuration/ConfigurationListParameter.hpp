#if !defined CONFIGURATION_LIST_PARAMETER_HPP
#define CONFIGURATION_LIST_PARAMETER_HPP

#include <string>

#include "ConfigurationParameter.hpp"

namespace Configuration
{
    template <class T, class U = std::list<T> > class ListParameter : public Parameter<U>
    {
    public:

        // Frobnicates the widget
        ListParameter(const U& initial_value = U());

        // Defrobnicates the widget.  Make this virtual if this class derives from something
        virtual ~ListParameter();

        virtual void fromString(const std::string& value);
        virtual void toString(std::string& value) const;
    };
}

#endif
