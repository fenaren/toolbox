#include <list>
#include <sstream>
#include <stdexcept>
#include <string>

#include "ConfigurationListParameter.hpp"

namespace Configuration
{

#define DEFINE_MIXED_LIST_PARAMETER_OPERATOR(OPERATOR, OP)      \
    template <class T>                                          \
    bool OPERATOR(const ListParameter<T>& lhs,                  \
                  const std::list<T>&     rhs)                  \
    {                                                           \
        return lhs OP ListParameter<T>(rhs);                    \
    }                                                           \
                                                                \
    template <class T>                                          \
    bool OPERATOR(const std::list<T>&     lhs,                  \
                  const ListParameter<T>& rhs)                  \
    {                                                           \
        return ListParameter<T>(lhs) OP rhs;                    \
    }

    //==========================================================================
    template <class T>
    ListParameter<T>::ListParameter(const std::list<T>& default_value_list) :
        ParameterBase(),
        value_list(default_value_list)
    {
    }

    //==========================================================================
    template <class T>
    ListParameter<T>::ListParameter(const ListParameter& parameter) :
        ParameterBase()
    {
        parameter.getValue(value_list);
    }

    //==========================================================================
    template <class T> ListParameter<T>::operator std::list<T>() const
    {
        return value_list;
    }

    //==========================================================================
    template <class T> ListParameter<T>::~ListParameter()
    {
    }

    //==========================================================================
    template <class T>
    void ListParameter<T>::updateValue(const std::string& value)
    {
        if (!isSet())
        {
            value_list.clear();
            set();
        }

        std::istringstream converter(value);

        T converted_value;
        converter >> converted_value;

        // Did the conversion go okay?
        if (!converter)
        {
            throw std::runtime_error("Error converting to list parameter type");
        }

        value_list.push_back(converted_value);
    }

    //==========================================================================
    template <class T>
    void ListParameter<T>::getValue(std::list<T>& value_list) const
    {
        value_list = this->value_list;
    }

    //==========================================================================
    template <class T> ListParameter<T>&
    ListParameter<T>::operator=(const ListParameter& list_parameter)
    {
        // Don't do anything if we're assigning to ourselves
        if (this != &list_parameter)
        {
            list_parameter.getValue(value_list);
            set();
        }

        return *this;
    }

    //==========================================================================
    template <class T> ListParameter<T>&
    ListParameter<T>::operator=(const std::list<T>& value_list)
    {
        this->value_list = value_list;
        set();

        return *this;
    }

    //==========================================================================
    template <class T>
    bool operator<(const ListParameter<T>& lhs, const ListParameter<T>& rhs)
    {
        std::list<T> lhs_value;
        std::list<T> rhs_value;

        lhs.getValue(lhs_value);
        rhs.getValue(rhs_value);

        return lhs_value < rhs_value;
    }

    DEFINE_MIXED_LIST_PARAMETER_OPERATOR(operator<, <);

    //==========================================================================
    template <class T>
    bool operator>(const ListParameter<T>& lhs, const ListParameter<T>& rhs)
    {
        return rhs < lhs;
    }

    DEFINE_MIXED_LIST_PARAMETER_OPERATOR(operator>, >);

    //==========================================================================
    template <class T>
    bool operator<=(const ListParameter<T>& lhs, const ListParameter<T>& rhs)
    {
        return !(lhs > rhs);
    }

    DEFINE_MIXED_LIST_PARAMETER_OPERATOR(operator<=, <=);

    //==========================================================================
    template <class T>
    bool operator>=(const ListParameter<T>& lhs, const ListParameter<T>& rhs)
    {
        return !(lhs < rhs);
    }

    DEFINE_MIXED_LIST_PARAMETER_OPERATOR(operator>=, >=);

    //==========================================================================
    template <class T>
    bool operator==(const ListParameter<T>& lhs, const ListParameter<T>& rhs)
    {
        std::list<T> lhs_value;
        std::list<T> rhs_value;

        lhs.getValue(lhs_value);
        rhs.getValue(rhs_value);

        return lhs_value == rhs_value;
    }

    DEFINE_MIXED_LIST_PARAMETER_OPERATOR(operator==, ==);

    //==========================================================================
    template <class T>
    bool operator!=(const ListParameter<T>& lhs, const ListParameter<T>& rhs)
    {
        return !(lhs == rhs);
    }

    DEFINE_MIXED_LIST_PARAMETER_OPERATOR(operator!=, !=);

    template class ListParameter<std::string>;

    template class ListParameter<char>;
    template class ListParameter<double>;
    template class ListParameter<float>;
    template class ListParameter<int>;
    template class ListParameter<long>;
    template class ListParameter<long double>;
    template class ListParameter<long long>;
    template class ListParameter<short>;
    template class ListParameter<unsigned char>;
    template class ListParameter<unsigned int>;
    template class ListParameter<unsigned long>;
    template class ListParameter<unsigned long long>;
    template class ListParameter<unsigned short>;

#define INSTANTIATE_LIST_PARAMETER_OPERATOR(OPERATOR)                   \
    template bool                                                       \
    OPERATOR(const ListParameter<std::string>&,                         \
             const ListParameter<std::string>&);                        \
                                                                        \
    template bool                                                       \
    OPERATOR(const ListParameter<std::string>&,                         \
             const std::list<std::string>&);                            \
    template bool                                                       \
    OPERATOR(const std::list<std::string>&,                             \
             const ListParameter<std::string>&);                        \
                                                                        \
    template bool OPERATOR(const ListParameter<char>&,                  \
                           const ListParameter<char>&);                 \
    template bool OPERATOR(const ListParameter<char>&, const std::list<char>&); \
    template bool OPERATOR(const std::list<char>&, const ListParameter<char>&); \
                                                                        \
    template bool OPERATOR(const ListParameter<double>&,                \
                           const ListParameter<double>&);               \
    template bool OPERATOR(const ListParameter<double>&, const std::list<double>&); \
    template bool OPERATOR(const std::list<double>&, const ListParameter<double>&); \
                                                                        \
    template bool OPERATOR(const ListParameter<float>&,                 \
                           const ListParameter<float>&);                \
    template bool OPERATOR(const ListParameter<float>&, const std::list<float>&); \
    template bool OPERATOR(const std::list<float>&, const ListParameter<float>&); \
                                                                        \
    template bool OPERATOR(const ListParameter<int>&,                   \
                           const ListParameter<int>&);                  \
    template bool OPERATOR(const ListParameter<int>&, const std::list<int>&); \
    template bool OPERATOR(const std::list<int>&, const ListParameter<int>&); \
                                                                        \
    template bool OPERATOR(const ListParameter<long>&,                  \
                           const ListParameter<long>&);                 \
    template bool OPERATOR(const ListParameter<long>&, const std::list<long>&); \
    template bool OPERATOR(const std::list<long>&, const ListParameter<long>&); \
                                                                        \
    template bool OPERATOR(const ListParameter<long double>&,           \
                           const ListParameter<long double>&);          \
    template bool OPERATOR(const ListParameter<long double>&,           \
                           const std::list<long double>&);              \
    template bool OPERATOR(const std::list<long double>&,               \
                           const ListParameter<long double>&);          \
                                                                        \
    template bool OPERATOR(const ListParameter<long long>&,             \
                           const ListParameter<long long>&);            \
    template bool OPERATOR(const ListParameter<long long>&,             \
                           const std::list<long long>&);                \
    template bool OPERATOR(const std::list<long long>&,                 \
                           const ListParameter<long long>&);            \
                                                                        \
    template bool OPERATOR(const ListParameter<short>&,                 \
                           const ListParameter<short>&);                \
    template bool OPERATOR(const ListParameter<short>&,                 \
                           const std::list<short>&);                    \
    template bool OPERATOR(const std::list<short>&,                     \
                           const ListParameter<short>&);                \
                                                                        \
    template bool OPERATOR(const ListParameter<unsigned char>&,         \
                           const ListParameter<unsigned char>&);        \
    template bool OPERATOR(const ListParameter<unsigned char>&,         \
                           const std::list<unsigned char>&);            \
    template bool OPERATOR(const std::list<unsigned char>&,             \
                           const ListParameter<unsigned char>&);        \
                                                                        \
    template bool OPERATOR(const ListParameter<unsigned int>&,          \
                           const ListParameter<unsigned int>&);         \
    template bool OPERATOR(const ListParameter<unsigned int>&,          \
                           const std::list<unsigned int>&);             \
    template bool OPERATOR(const std::list<unsigned int>&,              \
                           const ListParameter<unsigned int>&);         \
                                                                        \
    template bool OPERATOR(const ListParameter<unsigned long>&,         \
                           const ListParameter<unsigned long>&);        \
    template bool OPERATOR(const ListParameter<unsigned long>&,         \
                           const std::list<unsigned long>&);            \
    template bool OPERATOR(const std::list<unsigned long>&,             \
                           const ListParameter<unsigned long>&);        \
                                                                        \
    template bool OPERATOR(const ListParameter<unsigned long long>&,    \
                           const ListParameter<unsigned long long>&);   \
    template bool OPERATOR(const ListParameter<unsigned long long>&,    \
                           const std::list<unsigned long long>&);       \
    template bool OPERATOR(const std::list<unsigned long long>&,        \
                           const ListParameter<unsigned long long>&);   \
                                                                        \
    template bool OPERATOR(const ListParameter<unsigned short>&,        \
                           const ListParameter<unsigned short>&);       \
    template bool OPERATOR(const ListParameter<unsigned short>&,        \
                           const std::list<unsigned short>&);           \
    template bool OPERATOR(const std::list<unsigned short>&,            \
                           const ListParameter<unsigned short>&);

    INSTANTIATE_LIST_PARAMETER_OPERATOR(operator<);
    INSTANTIATE_LIST_PARAMETER_OPERATOR(operator>);
    INSTANTIATE_LIST_PARAMETER_OPERATOR(operator<=);
    INSTANTIATE_LIST_PARAMETER_OPERATOR(operator>=);
    INSTANTIATE_LIST_PARAMETER_OPERATOR(operator==);
    INSTANTIATE_LIST_PARAMETER_OPERATOR(operator!=);

}
