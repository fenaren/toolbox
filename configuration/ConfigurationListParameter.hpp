#if !defined CONFIGURATION_LIST_PARAMETER_HPP
#define CONFIGURATION_LIST_PARAMETER_HPP

#include <list>
#include <stdexcept>
#include <string>

#include "ConfigurationParameterBase.hpp"

namespace Configuration
{

    // Represents a configuration parameter consisting of a list of scalars. All
    // the intrinsic types and std::string are supported as parameter types, and
    // a variety of operators are overloaded to make this easy to use.
    template <class T> class ListParameter : public ParameterBase
    {
    public:

        friend class ListParameter_test;

        // cppcheck-suppress noExplicitConstructor
        ListParameter(const std::list<T>& default_value_list = std::list<T>());
        ListParameter(const ListParameter& parameter);

        // Defines how to convert a ListParameter<T> to a std::list<T>
        operator std::list<T>() const;

        // Destructor
        virtual ~ListParameter();

        // New values are taken with this method.
        virtual void updateValue(const std::string& value);

        // Returns a reference to the current value of the configuration
        // parameter.
        void getValue(std::list<T>& value_list) const;

        ListParameter& operator=(const ListParameter& parameter_list);
        ListParameter& operator=(const std::list<T>& parameter_list);

    private:

        std::list<T> value_list;
    };

#define DECLARE_CONFIGURATION_LIST_PARAMETER_OPERATOR(OPERATOR)         \
    template <class T> bool OPERATOR(const ListParameter<T>& lhs,       \
                                     const ListParameter<T>& rhs);      \
    template <class T> bool OPERATOR(const ListParameter<T>& lhs,       \
                                     const std::list<T>& rhs);          \
    template <class T> bool OPERATOR(const std::list<T>& lhs,           \
                                     const ListParameter<T>& rhs);

    DECLARE_CONFIGURATION_LIST_PARAMETER_OPERATOR(operator<);
    DECLARE_CONFIGURATION_LIST_PARAMETER_OPERATOR(operator>);
    DECLARE_CONFIGURATION_LIST_PARAMETER_OPERATOR(operator<=);
    DECLARE_CONFIGURATION_LIST_PARAMETER_OPERATOR(operator>=);
    DECLARE_CONFIGURATION_LIST_PARAMETER_OPERATOR(operator==);
    DECLARE_CONFIGURATION_LIST_PARAMETER_OPERATOR(operator!=);

}

#endif
