#if !defined CONFIGURATION_RELATIONAL_PARAMETER_HPP
#define CONFIGURATION_RELATIONAL_PARAMETER_HPP

#include <string>

#include "ConfigurationParameter.hpp"

namespace Configuration
{
    // Takes the definitions provided by the Parameter base class and adds relational operator
    // definitions.
    template <class T> class RelationalParameter : virtual public Parameter<T>
    {
    public:

        friend class RelationalParameter_test;

        explicit RelationalParameter(const T& initial_value = T());
        virtual ~RelationalParameter();
    };
}

// Save ourselves some time and use a macro to so we don't have to write these definitions six
// times.
#define DECLARE_CONFIGURATION_RELATIONAL_PARAMETER_OPERATOR(OPERATOR)   \
    template <class T> bool OPERATOR(const Configuration::RelationalParameter<T>& lhs, \
                                     const Configuration::RelationalParameter<T>& rhs); \
    template <class T> bool OPERATOR(const Configuration::RelationalParameter<T>& lhs, \
                                     const T&                                     rhs); \
    template <class T> bool OPERATOR(const T&                                     lhs, \
                                     const Configuration::RelationalParameter<T>& rhs); \
                                                                        \
    bool OPERATOR(const Configuration::RelationalParameter<std::string>& lhs, \
                  const char*                                            rhs); \
    bool OPERATOR(const char*                                            lhs, \
                  const Configuration::RelationalParameter<std::string>& rhs);

DECLARE_CONFIGURATION_RELATIONAL_PARAMETER_OPERATOR(operator<);
DECLARE_CONFIGURATION_RELATIONAL_PARAMETER_OPERATOR(operator>);
DECLARE_CONFIGURATION_RELATIONAL_PARAMETER_OPERATOR(operator<=);
DECLARE_CONFIGURATION_RELATIONAL_PARAMETER_OPERATOR(operator>=);
DECLARE_CONFIGURATION_RELATIONAL_PARAMETER_OPERATOR(operator==);
DECLARE_CONFIGURATION_RELATIONAL_PARAMETER_OPERATOR(operator!=);

#endif
