#if !defined CONFIGURATION_SIMPLE_PARAMETER_HPP
#define CONFIGURATION_SIMPLE_PARAMETER_HPP

#include <list>

#include "ConfigurationRelationalParameter.hpp"
#include "ConfigurationStreamParameter.hpp"

namespace Configuration
{
    template <class T> class SimpleParameter : public RelationalParameter<T>,
                                               public StreamParameter<T>
    {
    public:

        SimpleParameter(const T& initial_value = T());
        virtual ~SimpleParameter();
    };

    template <class T>
    class SimpleParameter<std::list<T> > : public RelationalParameter<std::list<T> >
    {
    public:

        SimpleParameter(const std::list<T>& initial_value = std::list<T>());
        virtual ~SimpleParameter();

        virtual void fromString(const std::string& value);
        virtual void toString(std::string& value) const;
    };
}

#endif
