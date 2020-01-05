#if !defined ARGUMENT_VALUE_LIST_HPP
#define ARGUMENT_VALUE_LIST_HPP

#include <list>
#include <string>

#include "Argument.hpp"

// Represents a type of argument for which we want to preserve every value
// given for it on the command line.  This really only works for optional
// arguments now, since positional arguments can only be specified once.
template <class T> class ArgumentValueList : public Argument
{
public:

    friend class ArgumentValueList_test;

    // Constructors
    explicit
    ArgumentValueList(const std::list<T>& default_values = std::list<T>());
    ArgumentValueList(const ArgumentValueList& argument_value_list);

    // Destructor
    virtual ~ArgumentValueList();

    // Defines the update interface required by Argument
    virtual void update(const std::string& value = "");

    // Returns all the values specified for this argument as a list.  Argument
    // values are returned in the order they were specified.
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
