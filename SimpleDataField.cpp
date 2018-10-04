#include <cstring>

#include "SimpleDataField.hpp"

#include "DataField.hpp"

//==============================================================================
template <class T> SimpleDataField<T>::SimpleDataField() :
    DataField()
{
}

//==============================================================================
template <class T> SimpleDataField<T>::SimpleDataField(const T& value) :
    DataField(),
    simple_data_field(value)
{
}

//==============================================================================
template <class T> SimpleDataField<T>::operator T() const
{
    return simple_data_field;
}

//==============================================================================
template <class T> SimpleDataField<T>::~SimpleDataField()
{
}

//==============================================================================
// Reads the field from the "buffer" memory location.
//==============================================================================
template <class T>
unsigned int SimpleDataField<T>::readRaw(const unsigned char* buffer)
{
    memcpy(&simple_data_field, buffer, sizeof(T));
    return sizeof(T);
}

//==============================================================================
// Writes the field to the "buffer" memory location.
//==============================================================================
template <class T>
unsigned int SimpleDataField<T>::writeRaw(unsigned char* buffer) const
{
    memcpy(buffer, &simple_data_field, sizeof(T));
    return sizeof(T);
}

//==============================================================================
// Returns the size of this field in bytes.  This will equal the number of bytes
// written by writeRaw() and read by readRaw().
//==============================================================================
template <class T> unsigned int SimpleDataField<T>::getLengthBytes() const
{
    return sizeof(T);
}

//==============================================================================
template <class T>
SimpleDataField<T>& SimpleDataField<T>::operator=(const T& simple_type)
{
    this->simple_data_field = simple_type;
    return *this;
}

// Explicitly instantiate the intrinsic types; as far as I know this is the
// best place for these instantiations to be located
template class SimpleDataField<char>;
template class SimpleDataField<double>;
template class SimpleDataField<float>;
template class SimpleDataField<int>;
template class SimpleDataField<long>;
template class SimpleDataField<long double>;
template class SimpleDataField<long long>;
template class SimpleDataField<short>;
template class SimpleDataField<unsigned char>;
template class SimpleDataField<unsigned int>;
template class SimpleDataField<unsigned long>;
template class SimpleDataField<unsigned long long>;
template class SimpleDataField<unsigned short>;
