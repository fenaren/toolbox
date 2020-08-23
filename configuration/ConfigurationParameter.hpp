#if !defined CONFIGURATION_PARAMETER_HPP
#define CONFIGURATION_PARAMETER_HPP

#include <list>
#include <string>

#include "ConfigurationRelationalParameter.hpp"
#include "ConfigurationStreamParameter.hpp"

namespace Configuration
{
    // The generic form of Parameter includes definitions for both relational and stream
    // operators.
    template <class T> class Parameter : public RelationalParameter<T>,
                                         public StreamParameter<T>
    {
    public:

        friend class Parameter_test;

        explicit Parameter(const T& initial_value = T());
        virtual ~Parameter();
    };

    // The partial specialization of Parameter for std::list only includes definitions
    // for relational operators (std::list doesn't support stream insertion and extraction).
    template <class T>
    class Parameter<std::list<T> > : public RelationalParameter<std::list<T> >
    {
    public:

        friend class Parameter_test;

        explicit Parameter(const std::list<T>& initial_value = std::list<T>());
        virtual ~Parameter();

        virtual void fromString(const std::string& value);
        virtual void toString(std::string& value) const;
    };
}

#endif
