#if !defined CONFIGURATION_LIST_PARAMETER_HPP
#define CONFIGURATION_LIST_PARAMETER_HPP

#include <string>

#include "ConfigurationParameter.hpp"

namespace Configuration
{
    template <class T, class U = std::list<T> > class ListParameter : public Parameter<U>
    {
    public:

        explicit ListParameter(const U& initial_value = U());
        virtual ~ListParameter();

        virtual void fromString(const std::string& value);
        virtual void toString(std::string& value) const;
    };
}

#endif
