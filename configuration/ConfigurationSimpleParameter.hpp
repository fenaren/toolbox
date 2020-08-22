#if !defined CONFIGURATION_SIMPLE_PARAMETER_HPP
#define CONFIGURATION_SIMPLE_PARAMETER_HPP

#include <list>
#include <string>

#include "ConfigurationRelationalParameter.hpp"
#include "ConfigurationStreamParameter.hpp"

namespace Configuration
{
    // The generic form of SimpleParameter includes definitions for both relational and stream
    // operators.
    template <class T> class SimpleParameter : public RelationalParameter<T>,
                                               public StreamParameter<T>
    {
    public:

        friend class SimpleParameter_test;

        explicit SimpleParameter(const T& initial_value = T());
        virtual ~SimpleParameter();
    };

    // The partial specialization of SimpleParameter for std::list only includes definitions
    // for relational operators (std::list doesn't support stream insertion and extraction).
    template <class T>
    class SimpleParameter<std::list<T> > : public RelationalParameter<std::list<T> >
    {
    public:

        friend class SimpleParameter_test;

        explicit SimpleParameter(const std::list<T>& initial_value = std::list<T>());
        virtual ~SimpleParameter();

        virtual void fromString(const std::string& value);
        virtual void toString(std::string& value) const;
    };
}

#endif
