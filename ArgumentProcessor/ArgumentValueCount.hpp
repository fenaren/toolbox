#if !defined ARGUMENT_VALUE_COUNT_HPP
#define ARGUMENT_VALUE_COUNT_HPP

#include <string>

#include "Argument.hpp"

class ArgumentValueCount : public Argument
{
public:

    // Frobnicates the widget
    ArgumentValueCount();

    ArgumentValueCount(const ArgumentValueCount& argument_value_count);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~ArgumentValueCount();

    virtual void update(const std::string& value = "");

    unsigned int getCount() const;

    ArgumentValueCount& operator=(
        const ArgumentValueCount& argument_value_count);

private:

    unsigned int count;
};

//==============================================================================
inline unsigned int ArgumentValueCount::getCount() const
{
    return count;
}

#endif
