#if !defined CONFIGURATION_RELATIONAL_PARAMETER_HPP
#define CONFIGURATION_RELATIONAL_PARAMETER_HPP

#include <string>

#include "ConfigurationParameter.hpp"

namespace Configuration
{
    template <class T> class RelationalParameter : virtual public Parameter<T>
    {
    public:

        friend class RelationalParameter_test;

        explicit RelationalParameter(const T& initial_value = T());
        virtual ~RelationalParameter();
    };
}

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
