#if !defined CONFIGURATION_PARAMETER_HPP
#define CONFIGURATION_PARAMETER_HPP

#include <string>

namespace Configuration
{
    // Allows ConfigurationParameters to go into data structures.
    class Parameter
    {
    public:

        Parameter();
        virtual ~Parameter();

        // Marks the ConfigurationParameter as unset. The value of an unset
        // ConfigurationParameter should not be used.
        void unset();

        // Is this ConfigurationParameter set (does the "value" field contain good data)?
        bool isSet() const;

        virtual void fromString(const std::string& value) = 0;
        virtual void toString(std::string& value) const = 0;

    protected:

        // The "value" field contains usable data if this is true, otherwise it doesn't.  What
        // is and isn't usable is determined by the user.
        bool set;
    };
}

//=============================================================================================
inline void Configuration::Parameter::unset()
{
    this->set = false;
}

//=============================================================================================
inline bool Configuration::Parameter::isSet() const
{
    return set;
}

#endif
