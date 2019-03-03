#include <cstdint>
#include <cstring>

#include "SimpleDataField.hpp"

#include "DataField.hpp"
#include "RawDataField.hpp"
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
template <class T> unsigned long SimpleDataField<T>::readRaw(
    std::uint8_t*   buffer,
    misc::ByteOrder source_byte_order)
{
    if (source_byte_order == getByteOrder())
    {
        memcpy(&simple_data_field, buffer, sizeof(T));
    }
    else
    {
        misc::byteswap(reinterpret_cast<std::uint8_t*>(&simple_data_field),
                       buffer,
                       sizeof(T));
    }

    return sizeof(T) * BITS_PER_BYTE;
}

//==============================================================================
template <class T> unsigned long SimpleDataField<T>::writeRaw(
    std::uint8_t*   buffer,
    misc::ByteOrder destination_byte_order) const
{
    if (destination_byte_order == getByteOrder())
    {
        memcpy(buffer, &simple_data_field, sizeof(T));
    }
    else
    {
        misc::byteswap(
            buffer,
            reinterpret_cast<const std::uint8_t*>(&simple_data_field),
            sizeof(T));
    }

    return sizeof(T) * BITS_PER_BYTE;
}

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
