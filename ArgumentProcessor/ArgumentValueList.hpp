#if !defined ARGUMENT_VALUE_LIST_HPP
#define ARGUMENT_VALUE_LIST_HPP

#include <list>
#include <string>

#include "Argument.hpp"

template <class T> class ArgumentValueList : public Argument
{
public:

    // Frobnicates the widget
    explicit ArgumentValueList(const std::list<T>& default_values);

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

//==============================================================================
template <class T>
inline void ArgumentValueList<T>::getValues(std::list<T>& values) const
{
    values = this->values;
}

template <class T> bool operator==(const ArgumentValueList<T>& lhs,
                                   const ArgumentValueList<T>& rhs);

template <class T> bool operator!=(const ArgumentValueList<T>& lhs,
                                   const ArgumentValueList<T>& rhs);

#endif
