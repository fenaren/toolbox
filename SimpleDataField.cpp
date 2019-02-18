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
template <class T>
unsigned long SimpleDataField<T>::readRaw(std::uint8_t* buffer,
                                          unsigned long offset_bits)
{
    return DataField::readRaw(buffer, offset_bits);
}

//==============================================================================
template <class T> unsigned long SimpleDataField<T>::readRaw(
    std::uint8_t*   buffer,
    misc::ByteOrder source_byte_order,
    unsigned long   offset_bits)
{
    normalizeMemoryLocation(buffer, offset_bits);

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
template <class T>
unsigned long SimpleDataField<T>::writeRaw(std::uint8_t* buffer,
                                           unsigned long offset_bits) const
{
    return DataField::writeRaw(buffer, offset_bits);
}

//==============================================================================
template <class T> unsigned long SimpleDataField<T>::writeRaw(
    std::uint8_t*   buffer,
    misc::ByteOrder destination_byte_order,
    unsigned long   offset_bits) const
{
    normalizeMemoryLocation(buffer, offset_bits);

    // Unaligned types are expected to be uncommon
    if (offset_bits == 0)
    {
        copyOptionalSwap(buffer, destination_byte_order);
    }
    else
    {
        // 0 < offset_bytes < 8 due to normalizeMemoryLocation()

        unsigned int working_size = sizeof(T) + 1;

        // Copy the field data to a temporary location.  We'll handle the bit
        // shifting nonsense in there.
        std::uint8_t working_buffer[working_size];
        working_buffer[working_size - 1] = 0;
        copyOptionalSwap(working_buffer, destination_byte_order);

        // Create a mask for the bits we want
        std::uint8_t mask[working_size];
        memset(mask, 0xFF, sizeof(T));
        mask[working_size - 1] = 0;

        // Use a RawDataField to shift both the data we want and the
        // corrsponding mask over into the extra byte.  Counts on RawDataField
        // shift behavior of shifting in zeros.  RawDataField shifts treat the
        // whole bitfield as if it were a single large integer for shifting
        // purposes so we may need shiftLeft or shiftRight depending on the
        // endianness of the host.
        RawDataField working_bitfield(
            working_buffer, working_size, misc::BYTES, misc::MS_ZERO, false);
        RawDataField mask_bitfield(
            mask, working_size, misc::BYTES, misc::MS_ZERO, false);

        if (getByteOrder() == misc::ENDIAN_BIG)
        {
            working_bitfield.shiftRight(offset_bits);
            mask_bitfield.shiftRight(offset_bits);
        }
        else
        {
            working_bitfield.shiftLeft(offset_bits);
            mask_bitfield.shiftLeft(offset_bits);
        }

        // Mask in the bits we want to set, preserving the setting of the bits
        // we don't want to set
        for (unsigned int i = 0; i < working_size; ++i)
        {
            buffer[i] &= ~mask[i];
            buffer[i] |= working_buffer[i];
        }
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

//==============================================================================
template <class T> void SimpleDataField<T>::copyOptionalSwap(
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
}
