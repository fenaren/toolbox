#include <cstring>

#include "SimpleDataField.hpp"

#include "DataField.hpp"
#include "misc.hpp"

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
// Copy constructor
//==============================================================================
template <class T>
SimpleDataField<T>::SimpleDataField(const SimpleDataField<T>& simple_data_field)
{
    this->simple_data_field = simple_data_field.getValue();
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
// Reads the data field from the "buffer" memory location without considering
// byte ordering.
//==============================================================================
template <class T>
unsigned long SimpleDataField<T>::readRaw(const unsigned char* buffer,
                                          unsigned int         offset_bits)
{
    return DataField::readRaw(buffer, offset_bits);
}

//==============================================================================
// Reads the data field from the "buffer" memory location, swapping if the
// source byte order does not match the byte ordering of this field.
//==============================================================================
template <class T> unsigned long SimpleDataField<T>::readRaw(
    const unsigned char* buffer,
    misc::ByteOrder      source_byte_order,
    unsigned int         offset_bits)
{
    if (source_byte_order == getByteOrder())
    {
        memcpy(&simple_data_field, buffer, sizeof(T));
    }
    else
    {
        misc::byteswap(reinterpret_cast<unsigned char*>(&simple_data_field),
                       buffer,
                       sizeof(T));
    }

    return sizeof(T);
}

//==============================================================================
// Writes the data field to the "buffer" memory location without considering
// byte ordering.
//==============================================================================
template <class T>
unsigned long SimpleDataField<T>::writeRaw(unsigned char* buffer,
                                           unsigned int   offset_bits) const
{
    return DataField::writeRaw(buffer, offset_bits);
}

//==============================================================================
// Writes the data field to the "buffer" memory location, swapping at the
// destination if the destination byte order does not match the byte ordering of
// this field.
//==============================================================================
template <class T> unsigned long SimpleDataField<T>::writeRaw(
    unsigned char*  buffer,
    misc::ByteOrder destination_byte_order,
    unsigned int    offset_bits) const
{
    if (destination_byte_order == getByteOrder())
    {
        memcpy(buffer, &simple_data_field, sizeof(T));
    }
    else
    {
        misc::byteswap(
            buffer,
            reinterpret_cast<const unsigned char*>(&simple_data_field),
            sizeof(T));
    }

    return sizeof(T);
}

//==============================================================================
// Returns the size of this field in bytes.  This will equal the number of bytes
// written by writeRaw() and read by readRaw().
//==============================================================================
template <class T> unsigned long SimpleDataField<T>::getLengthBits() const
{
    return sizeof(T) * BITS_PER_BYTE;
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
