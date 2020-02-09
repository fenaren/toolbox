#if !defined CONFIGURATION_VALUE_COUNT_HPP
#define CONFIGURATION_VALUE_COUNT_HPP

#include <string>

#include "ConfigurationValueBase.hpp"

// Sometimes we only care about the number of times a configuration value is
// specified, and not the actual value or values in the specification (its
// "value" is the number of times it appears).  This class represents this type
// of configuration value.  The getCount() method returns the number of times
// the configuration value is specified.
class ConfigurationValueCount : public ConfigurationValueBase
{
public:

    friend class ConfigurationValueCount_test;

    // Constructors
    explicit ConfigurationValueCount(unsigned int default_count = 0);
    ConfigurationValueCount(
        const ConfigurationValueCount& argument_value_count);

    // Destructor
    virtual ~ConfigurationValueCount();

    // Defines the update interface required by ConfigurationValueBase
    virtual void setValue(const std::string& value);

    // Returns the number of times the argument appears in the command list.
    unsigned int getCount() const;

    ConfigurationValueCount&
    operator=(const ConfigurationValueCount& argument_value_count);
    ConfigurationValueCount& operator=(unsigned int count);

private:

    unsigned int count;
};

//==============================================================================
inline unsigned int ConfigurationValueCount::getCount() const
{
    return count;
}

bool operator<(const ConfigurationValueCount& lhs,  const ConfigurationValueCount& rhs);
bool operator>(const ConfigurationValueCount& lhs,  const ConfigurationValueCount& rhs);
bool operator<=(const ConfigurationValueCount& lhs, const ConfigurationValueCount& rhs);
bool operator>=(const ConfigurationValueCount& lhs, const ConfigurationValueCount& rhs);
bool operator==(const ConfigurationValueCount& lhs, const ConfigurationValueCount& rhs);
bool operator!=(const ConfigurationValueCount& lhs, const ConfigurationValueCount& rhs);

#endif
