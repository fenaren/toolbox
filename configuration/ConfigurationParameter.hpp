#if !defined CONFIGURATION_PARAMETER_HPP
#define CONFIGURATION_PARAMETER_HPP

#include <stdexcept>
#include <string>

namespace Configuration
{
    // ConfigurationParameter is a simple class for associating a small amount of metadata with
    // a piece of data (the "value" field).  It's basically a simple implementation of the data
    // element concept (see "https://en.wikipedia.org/wiki/Data_element").
    template <class T> class Parameter
    {
    public:

        friend class Parameter_test;

        // Constructors
        // cppcheck-suppress noExplicitConstructor
        Parameter(const T& initial_value = T());
        Parameter(const Parameter& parameter);

        // Defines how to convert a Parameter<T> to a T
        operator T() const;

        // Destructor
        ~Parameter();

        // Marks the ConfigurationParameter as unset. The value of an unset
        // ConfigurationParameter should not be used.
        void unset();

        // Is this ConfigurationParameter set (does the "value" field contain good data)?
        bool isSet() const;

        void setValue(const T& value);

        // Returns the current value on the stack.  Try to use the other getValue() method if T
        // is large in memory.
        T getValue() const;

        // Returns a reference to the current value of the configuration parameter.
        void getValue(T& value) const;

        Parameter& operator=(const Parameter& parameter);
        Parameter& operator=(const T& parameter);

    private:

        T value;

        // The "value" field contains usable data if this is true, otherwise it doesn't.  What
        // is and isn't usable is determined by the user.
        bool set;
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
