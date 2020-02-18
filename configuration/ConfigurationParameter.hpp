#if !defined CONFIGURATION_PARAMETER_HPP
#define CONFIGURATION_PARAMETER_HPP

#include <stdexcept>
#include <string>

#include "ConfigurationParameterBase.hpp"

namespace Configuration
{

    // Represents a scalar configuration parameter. All the intrinsic types and
    // std::string are supported as parameter types, and a variety of operators
    // are overloaded to make this easy to use.
    template <class T> class Parameter : public ParameterBase
    {
    public:

        friend class Parameter_test;

        // Constructors
        // cppcheck-suppress noExplicitConstructor
        Parameter(const T& parameter_default = T());
        Parameter(const Parameter& parameter);

        // Defines how to convert a Parameter<T> to a T
        operator T() const;

        // Destructor
        virtual ~Parameter();

        // Allows Processors to set the value regardless of templatized type.
        virtual void updateValue(const std::string& value);

        // Returns the current value on the stack.  Try to use the other
        // getValue() method if T is large in memory.
        T getValue() const;

        // Returns a reference to the current value of the configuration
        // parameter.
        void getValue(T& value) const;

        Parameter& operator=(const Parameter& parameter);
        Parameter& operator=(const T& parameter);

    private:

        T value;
    };

#define DECLARE_CONFIGURATION_PARAMETER_OPERATOR(OPERATOR)      \
    template <class T> bool OPERATOR(const Parameter<T>& lhs,   \
                                     const Parameter<T>& rhs);  \
    template <class T> bool OPERATOR(const Parameter<T>& lhs,   \
                                     const T&            rhs);  \
    template <class T> bool OPERATOR(const T&            lhs,   \
                                     const Parameter<T>& rhs);  \
                                                                \
    bool OPERATOR(const Parameter<std::string>& lhs,            \
                  const char* rhs);                             \
    bool OPERATOR(const char* lhs,                              \
                  const Parameter<std::string>& rhs);

    DECLARE_CONFIGURATION_PARAMETER_OPERATOR(operator<);
    DECLARE_CONFIGURATION_PARAMETER_OPERATOR(operator>);
    DECLARE_CONFIGURATION_PARAMETER_OPERATOR(operator<=);
    DECLARE_CONFIGURATION_PARAMETER_OPERATOR(operator>=);
    DECLARE_CONFIGURATION_PARAMETER_OPERATOR(operator==);
    DECLARE_CONFIGURATION_PARAMETER_OPERATOR(operator!=);

}

#endif
