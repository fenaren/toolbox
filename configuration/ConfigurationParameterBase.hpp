#if !defined CONFIGURATION_PARAMETER_BASE_HPP
#define CONFIGURATION_PARAMETER_BASE_HPP

#include <string>

namespace Configuration
{
    // The ConfigurationParameter tree of classes is for associating a small amount of metadata
    // (the "set" field) with a piece of data (the "value" field).  It's a simple
    // implementation of the data element concept (see
    // "https://en.wikipedia.org/wiki/Data_element"). The point is to use this metadata to
    // permit only a specific (the first, usually) source of configuration information to set
    // the value of a ConfigurationParameter.

    // All ConfigurationParameter derived classes derive from here.  ConfigurationParameter
    // functionality not dependent on a specific ConfigurationParameter type instantiation is
    // defined here. For this reason an actual "value" isn't defined here, that's done in
    // ConfigurationParameterTemplate.
    class ParameterBase
    {
    public:

        ParameterBase();
        virtual ~ParameterBase();

        // Marks the ConfigurationParameter as unset. An unset ConfigurationParameter may have
        // its value set after construction time.
        void unset();

        // Does this ConfigurationParameter have a set value? If so its value cannot be set
        // after construction time, otherwise it can.
        bool isSet() const;

        // These methods define how ConfigurationParameters go to and from
        // std::strings. ConfigurationProcessors use these to set ConfigurationParameter
        // values.
        virtual void fromString(const std::string& value) = 0;
        virtual void toString(std::string& value) const = 0;

    protected:

        // Does this ConfigurationParameter have a set value? If so its value cannot be set
        // after construction time, otherwise it can.
        bool set;
    };
}

//=============================================================================================
inline void Configuration::ParameterBase::unset()
{
    this->set = false;
}

//=============================================================================================
inline bool Configuration::ParameterBase::isSet() const
{
    return set;
}

#endif
