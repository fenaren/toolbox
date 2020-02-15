#if !defined CONFIGURATION_VALUE_BASE_HPP
#define CONFIGURATION_VALUE_BASE_HPP

#include <string>

// ConfigurationValue inherits from this, defining an interface by which all
// ConfigurationValues can be modified regardless of templatized type.
class ConfigurationValueBase
{
public:

    ConfigurationValueBase();
    ConfigurationValueBase(const ConfigurationValueBase&);

    virtual ~ConfigurationValueBase();

    // This is how Processors push values into ConfigurationValues generically
    virtual void setValue(const std::string& value) = 0;

    // Returns true if this configuration value has been set after construction.
    bool isSet() const;

    ConfigurationValueBase& operator=(const ConfigurationValueBase&);

protected:

    void set();

private:

    bool _set;
};

//==============================================================================
inline void ConfigurationValueBase::set()
{
    _set = true;
}

//==============================================================================
inline bool ConfigurationValueBase::isSet() const
{
    return _set;
}

#endif
