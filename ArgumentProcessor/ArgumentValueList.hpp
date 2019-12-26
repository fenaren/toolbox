#if !defined ARGUMENT_VALUE_LIST_HPP
#define ARGUMENT_VALUE_LIST_HPP

#include <list>

#include "Argument.hpp"

template <class T> class ArgumentValueList : public Argument
{
public:

    // Frobnicates the widget
    ArgumentValueList();

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~ArgumentValueList();

private:

    std::list<T> values;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    ArgumentValueList(const ArgumentValueList&);
    ArgumentValueList& operator=(const ArgumentValueList&);
};

#endif
