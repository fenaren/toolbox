#if !defined CONFIGURATION_PARAMETER_BASE_HPP
#define CONFIGURATION_PARAMETER_BASE_HPP

#include <string>

namespace Configuration
{

    // ConfigurationParameter inherits from this, defining an interface by which
    // all ConfigurationParameters can be modified regardless of templatized
    // type.
    class ParameterBase
    {
    public:

        ParameterBase();
        ParameterBase(const ParameterBase&);

        virtual ~ParameterBase();

        // This is how Processors push values into Parameters generically
        virtual void updateValue(const std::string& value) = 0;

        // Returns true if this configuration value has been set after
        // construction.
        bool isSet() const;

        ParameterBase& operator=(const ParameterBase&);

    protected:

        void set();

    private:

        bool _set;
    };

    //==========================================================================
    inline void ParameterBase::set()
    {
        _set = true;
    }

    //==========================================================================
    inline bool ParameterBase::isSet() const
    {
        return _set;
    }

}

#endif
