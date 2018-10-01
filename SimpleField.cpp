#include <cstring>
#include <string>

#include "SimpleField.hpp"

#include "Field.hpp"

//==============================================================================
template <class T>
SimpleField<T>::SimpleField(const std::string& name) :
    Field(name)
{
}

//==============================================================================
template <class T>
SimpleField<T>::~SimpleField()
{
}

//==============================================================================
// Reads the field from the "buffer" memory location.
//==============================================================================
template <class T>
unsigned int SimpleField<T>::readRaw(const unsigned char* buffer)
{
    memcpy(&simple_field, buffer, sizeof(T));

    return sizeof(T);
}

//==============================================================================
// Writes the field to the "buffer" memory location.
//==============================================================================
template <class T>
unsigned int SimpleField<T>::writeRaw(unsigned char* buffer) const
{
    memcpy(buffer, &simple_field, sizeof(T));

    return sizeof(T);
}

//==============================================================================
// Returns the size of this field in bytes.  This will equal the number of bytes
// written by writeRaw() and read by readRaw().
//==============================================================================
template <class T>
unsigned int SimpleField<T>::getLengthBytes() const
{
    return sizeof(T);
}

// Explicitly instantiate the intrinsic types; as far as I know this is the
// best place for these instantiations to be located
template class SimpleField<char>;
template class SimpleField<double>;
template class SimpleField<float>;
template class SimpleField<int>;
template class SimpleField<long>;
template class SimpleField<long double>;
template class SimpleField<long long>;
template class SimpleField<short>;
template class SimpleField<unsigned char>;
template class SimpleField<unsigned int>;
template class SimpleField<unsigned long>;
template class SimpleField<unsigned long long>;
template class SimpleField<unsigned short>;
