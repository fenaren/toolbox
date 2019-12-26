#if !defined ARGUMENT_VALUE_LIST_HPP
#define ARGUMENT_VALUE_LIST_HPP

#include <list>
#include <string>

#include "Argument.hpp"

template <class T> class ArgumentValueList : public Argument
{
public:

    // Frobnicates the widget
    ArgumentValueList();

    ArgumentValueList(const ArgumentValueList& argument_value_list);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~ArgumentValueList();

    virtual void update(const std::string& value = "");

    void getValues(std::list<T>& values) const;

    ArgumentValueList& operator=(const ArgumentValueList& argument_value_list);

private:

    std::list<T> values;
};

#endif
