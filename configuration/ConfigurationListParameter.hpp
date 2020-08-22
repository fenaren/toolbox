#if !defined CONFIGURATION_LIST_PARAMETER_HPP
#define CONFIGURATION_LIST_PARAMETER_HPP

#include <list>
#include <string>

#include "ConfigurationRelationalParameter.hpp"

namespace Configuration
{
    template <class T> class ListParameter : public RelationalParameter<std::list<T> >
    {
    public:

        explicit ListParameter(const std::list<T>& initial_value = std::list<T>());
        virtual ~ListParameter();

        virtual void fromString(const std::string& value);
        virtual void toString(std::string& value) const;
    };
}

#endif
