#if !defined CONFIGURATION_VALUE_BASE_HPP
#define CONFIGURATION_VALUE_BASE_HPP

// ConfigurationValue inherits from this, defining an interface by which all
// ConfigurationValues can be modified regardless of templatized type.
class ConfigurationValueBase
{
public:

    // Does nothing
    ConfigurationValueBase();
    virtual ~ConfigurationValueBase();

    // This is how Processors push values into ConfigurationValues generically
    virtual void setValue(const std::string& value) = 0;

private:

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    ConfigurationValueBase(const ConfigurationValueBase&);
    ConfigurationValueBase& operator=(const ConfigurationValueBase&);
};

#endif
