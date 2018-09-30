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
