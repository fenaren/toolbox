#if !defined OPTIONAL_VALUE_ARGUMENT_HPP
#define OPTIONAL_VALUE_ARGUMENT_HPP

#include <list>
#include <string>

#include "OptionalArgument.hpp"

class OptionalValueArgument : public OptionalArgument
{
public:

    // Frobnicates the widget
    OptionalValueArgument();

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~OptionalValueArgument();

    void setValue(const std::string& value);

    void getLastValue(std::string& value) const;

    template <class T> T getLastValue() const;

    void getValues(std::list<std::string>& values) const;

    template <class T> void getValues(std::list<T>& values) const;

private:

    std::list<std::string> values;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    OptionalValueArgument(const OptionalValueArgument&);
    OptionalValueArgument& operator=(const OptionalValueArgument&);
};

//==============================================================================
inline void OptionalValueArgument::setValue(const std::string& value)
{
    OptionalArgument::set();

    values.push_back(value);
}

//==============================================================================
inline void OptionalValueArgument::getLastValue(std::string& last_value) const
{
    last_value = values.back();
}

//==============================================================================
inline
void OptionalValueArgument::getValues(std::list<std::string>& values) const
{
    values = this->values;
}

#endif
