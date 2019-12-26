#if !defined ARGUMENT_VALUE_COUNT_HPP
#define ARGUMENT_VALUE_COUNT_HPP

#include "Argument.hpp"

class ArgumentValueCount : public Argument
{
public:

    // Frobnicates the widget
    ArgumentValueCount();

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    ~ArgumentValueCount();

    void increment();

    unsigned int getCount() const;

private:

    unsigned int count;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    ArgumentValueCount(const ArgumentValueCount&);
    ArgumentValueCount& operator=(const ArgumentValueCount&);
};

//==============================================================================
inline void ArgumentValueCount::increment()
{
    count++;
}

//==============================================================================
inline unsigned int ArgumentValueCount::getCount() const
{
    return count;
}

#endif
