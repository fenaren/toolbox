#if !defined CONFIGURATION_NOOP_PARAMETER_HPP
#define CONFIGURATION_NOOP_PARAMETER_HPP

#include <string>

#include "ConfigurationParameter.hpp"

namespace Configuration
{
    template <class T> class NoopParameter : public Parameter<T>
    {
    public:

        explicit NoopParameter(const T& initial_value = T());
        virtual ~NoopParameter();

        virtual void fromString(const std::string& value);
        virtual void toString(std::string& value) const;

    private:

        NoopParameter(const NoopParameter&);
        NoopParameter& operator=(const NoopParameter&);
    };
}

#endif
