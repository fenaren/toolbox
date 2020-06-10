#if !defined CONFIGURATION_PARAMETER_BASE_HPP
#define CONFIGURATION_PARAMETER_BASE_HPP

#include <string>

namespace Configuration
{
    // ParameterBases can be "unset" or "set". Unset configuration parameters have never had
    // their value set after construction (using updateValue()), and set configuration
    // parameters have.  This allows programs to determine if ParameterBases have been
    // specified by a user at runtime (set) or if the default is in use (unset).
    class ParameterBase
    {
    public:

        // Does nothing
        ParameterBase();
        virtual ~ParameterBase();

        // Sets the is_set data member to false, marking the ConfigurationParameterBase as
        // "unset".
        void unset();

        // Is this ConfigurationParameterBase set?
        bool isSet() const;

        // New values are taken with this method.
        virtual void setValue(const std::string& value) = 0;

    protected:

        // Sets the is_set data member to true, marking the ConfigurationParameterBase as
        // "set".  Only derived classes can do this because this operation is only supposed to
        // happen when updateValue() is called.
        void set();

    private:

        // The "set" or "unset" status of this ConfigurationParameterBase.
        bool is_set;

        ParameterBase(const ParameterBase&);
        ParameterBase& operator=(const ParameterBase&);
    };

    //=========================================================================================
    inline void ParameterBase::unset()
    {
        is_set = false;
    }

    //=========================================================================================
    inline bool ParameterBase::isSet() const
    {
        return is_set;
    }

    //=========================================================================================
    inline void ParameterBase::set()
    {
        is_set = true;
    }
}

#endif
