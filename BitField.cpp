#include <cstring>
#include <new>
#include <stdexcept>

#include "BitField.hpp"

#include "RawDataField.hpp"
#include "misc.hpp"

//==============================================================================
BitField::BitField(unsigned long length_bits) :
    RawDataField(true, misc::LS_ZERO),
    length_bits(length_bits)
{
    bit_field_raw = new std::uint8_t[getUsedBytes()];
    memset(bit_field_raw, 0, getUsedBytes());
}

//==============================================================================
BitField::BitField(std::uint8_t* buffer,
                   unsigned long length_bits,
                   bool          memory_internal) :
    RawDataField(memory_internal, misc::LS_ZERO),
    length_bits(length_bits)
{
    if (memory_internal)
    {
        bit_field_raw = new std::uint8_t[getUsedBytes()];
        readRaw(buffer);
    }
    else
    {
        bit_field_raw = buffer;
    }
}

//==============================================================================
BitField::BitField(const BitField& bit_field) :
    RawDataField(true, bit_field.getIndexingMode())
{
    length_bits = bit_field.getLengthBits();

    bit_field_raw = new std::uint8_t[getUsedBytes()];

    bit_field.writeRaw(bit_field_raw);
}

//==============================================================================
BitField::~BitField()
{
    if (getMemoryInternal())
    {
        delete[] bit_field_raw;
    }
}

//==============================================================================
unsigned long BitField::readRaw(std::uint8_t* buffer,
                                unsigned long offset_bits)
{
    return DataField::readRaw(buffer, offset_bits);
}

//==============================================================================
unsigned long BitField::readRaw(std::uint8_t*   buffer,
                                misc::ByteOrder source_byte_order,
                                unsigned long   offset_bits)
{
    // No byteswapping regardless of "source_byte_order" setting
    memcpy(bit_field_raw, buffer, getUsedBytes());
    return static_cast<unsigned long>(getUsedBytes()) * BITS_PER_BYTE;
}

//==============================================================================
unsigned long BitField::writeRaw(std::uint8_t* buffer,
                                 unsigned long offset_bits) const
{
    return DataField::writeRaw(buffer, offset_bits);
}

//==============================================================================
unsigned long BitField::writeRaw(std::uint8_t*   buffer,
                                 misc::ByteOrder destination_byte_order,
                                 unsigned long   offset_bits) const
{
    // No byteswapping regardless of "destination_byte_order" setting
    memcpy(buffer, bit_field_raw, getUsedBytes());
    return static_cast<unsigned long>(getUsedBytes()) * BITS_PER_BYTE;
}

//==============================================================================
bool BitField::getBit(unsigned long index) const
{
    throwIfIndexOutOfRange(index, length_bits);

    // This returns the index of the byte we want and the index of the bit
    // within that byte
    std::ldiv_t div_result = std::ldiv(index, BITS_PER_BYTE);

    // This is the byte we want but only if byte indexing mode is most
    // significant byte first
    std::uint8_t target_byte = bit_field_raw[div_result.quot];

    // Now we have the right byte but we still need to find the right bit;
    // div_result.rem has the index

    if (getIndexingMode() == misc::LS_ZERO)
    {
        target_byte >>= div_result.rem;
    }
    else
    {
        target_byte >>= BITS_PER_BYTE - div_result.rem - 1;
    }

    return (target_byte & 0x1) == 1;
}

//==============================================================================
void BitField::setBit(unsigned long index, bool value)
{
    throwIfIndexOutOfRange(index, length_bits);

    std::uint8_t mask = 1;

    std::uint8_t target_byte = 0;
    if (value)
    {
        target_byte = 1;
    }

    // This returns the index of the byte we want and the index of the bit
    // within that byte
    std::ldiv_t div_result = std::ldiv(index, BITS_PER_BYTE);

    // This is the proper amount to shift if bit indexing mode is least
    // significant zero
    unsigned int shift_amount = div_result.rem;
    if (getIndexingMode() == misc::MS_ZERO)
    {
        shift_amount = BITS_PER_BYTE - div_result.rem - 1;
    }

    target_byte <<= shift_amount;
    mask <<= shift_amount;

    // We have the byte and mask shifted properly, now we just have to write the
    // byte into the proper place in raw_bit_field

    unsigned int byte_index = div_result.quot;

    // Mask the bit setting in
    bit_field_raw[byte_index] &= ~mask;
    bit_field_raw[byte_index] |= target_byte;
}

//==============================================================================
template <class T> void BitField::getBitsAsNumericType(
    T&            type_var,
    unsigned long start_bit,
    unsigned long count) const
{
    throwIfIndexOutOfRange(start_bit + count - 1, length_bits);

    if (count > sizeof(T) * BITS_PER_BYTE)
    {
        throw std::out_of_range("Not enough bits in the destination type");
    }

    // We could not do this and leave irrelevant bits untouched, but that
    // wouldn't match the usage convention of pretty much every other getter
    // class member function ever
    type_var = 0;

    // Use the given variable as if it were a bitfield, and set bits inside it
    BitField working_bitfield(reinterpret_cast<std::uint8_t*>(&type_var),
                              sizeof(T) * BITS_PER_BYTE,
                              false);

    // Copy all the bits; an alternative implementation would be to memcpy the
    // relevant data over, shift down and then mask out the irrelevant bits
    for (unsigned long i = 0; i < count; ++i)
    {
        working_bitfield.setBit(i, getBit(start_bit + i));
    }
}

// Use this macro to instantiate getBitsAsNumericType() for all the intrinsic
// numeric types.  "char" is arguably not a numeric type but let's include it
// since it's sometimes useful to use it as if it were a numeric type
#define INSTANTIATE_GETBITSASNUMERICTYPE(Type)                          \
    template void                                                       \
    BitField::getBitsAsNumericType(Type&, unsigned long, unsigned long) const;

INSTANTIATE_GETBITSASNUMERICTYPE(char);
INSTANTIATE_GETBITSASNUMERICTYPE(double);
INSTANTIATE_GETBITSASNUMERICTYPE(float);
INSTANTIATE_GETBITSASNUMERICTYPE(int);
INSTANTIATE_GETBITSASNUMERICTYPE(long);
INSTANTIATE_GETBITSASNUMERICTYPE(long double);
INSTANTIATE_GETBITSASNUMERICTYPE(long long);
INSTANTIATE_GETBITSASNUMERICTYPE(short);
INSTANTIATE_GETBITSASNUMERICTYPE(unsigned char);
INSTANTIATE_GETBITSASNUMERICTYPE(unsigned int);
INSTANTIATE_GETBITSASNUMERICTYPE(unsigned long);
INSTANTIATE_GETBITSASNUMERICTYPE(unsigned long long);
INSTANTIATE_GETBITSASNUMERICTYPE(unsigned short);

//==============================================================================
template <class T> void BitField::setBitsAsNumericType(
    T             type_var,
    unsigned long start_bit,
    unsigned long count)
{
    throwIfIndexOutOfRange(start_bit + count - 1, length_bits);

    if (count > sizeof(T) * BITS_PER_BYTE)
    {
        throw std::out_of_range("Not enough bits in the source type");
    }

    // Use the given variable as if it were a bitfield, and set bits inside it
    BitField working_bitfield(reinterpret_cast<std::uint8_t*>(&type_var),
                              sizeof(T),
                              false);

    // Copy all the bits; an alternative implementation would be to memcpy the
    // relevant data over, shift down and then mask out the irrelevant bits
    for (unsigned long i = 0; i < count; ++i)
    {
       setBit(start_bit + i, working_bitfield.getBit(i));
    }
}

// Use this macro to instantiate setBitsAsNumericType() for all the intrinsic
// numeric types.  "char" is arguably not a numeric type but let's include it
// since it's sometimes useful to use it as if it were a numeric type
#define INSTANTIATE_SETBITSASNUMERICTYPE(Type)                          \
    template void                                                       \
    BitField::setBitsAsNumericType(Type, unsigned long, unsigned long);

INSTANTIATE_SETBITSASNUMERICTYPE(char);
INSTANTIATE_SETBITSASNUMERICTYPE(double);
INSTANTIATE_SETBITSASNUMERICTYPE(float);
INSTANTIATE_SETBITSASNUMERICTYPE(int);
INSTANTIATE_SETBITSASNUMERICTYPE(long);
INSTANTIATE_SETBITSASNUMERICTYPE(long double);
INSTANTIATE_SETBITSASNUMERICTYPE(long long);
INSTANTIATE_SETBITSASNUMERICTYPE(short);
INSTANTIATE_SETBITSASNUMERICTYPE(unsigned char);
INSTANTIATE_SETBITSASNUMERICTYPE(unsigned int);
INSTANTIATE_SETBITSASNUMERICTYPE(unsigned long);
INSTANTIATE_SETBITSASNUMERICTYPE(unsigned long long);
INSTANTIATE_SETBITSASNUMERICTYPE(unsigned short);

//==============================================================================
void BitField::shiftLeft(unsigned long shift_bits)
{
    if (shift_bits >= length_bits)
    {
        throw std::runtime_error(
            "Requested shift amount must be less than the width of the field");
    }

    // A shift of 0 bits is a no-op
    if (shift_bits == 0)
    {
        return;
    }

    for (unsigned long i = length_bits - 1; i != shift_bits - 1; --i)
    {
        setBit(i, getBit(i - shift_bits));
    }

    // Shift in zeros
    for (unsigned long i = shift_bits - 1; i != 0; --i)
    {
        setBit(i, false);
    }

    // Least significant bit will always be 0
    setBit(0, false);
}

//==============================================================================
void BitField::shiftRight(unsigned long shift_bits)
{
    if (shift_bits >= length_bits)
    {
        throw std::runtime_error(
            "Requested shift amount must be less than the width of the field");
    }

    // A shift of 0 bits is a no-op
    if (shift_bits == 0)
    {
        return;
    }

    // Copy over the shifted bits
    for (unsigned long i = 0; i < length_bits - shift_bits; i++)
    {
        setBit(i, getBit(i + shift_bits));
    }

    // Shift in zeros
    for (unsigned long i = length_bits - shift_bits; i < length_bits; i++)
    {
        setBit(i, false);
    }
}

//==============================================================================
BitField& BitField::operator=(const BitField& bit_field)
{
    if (this != &bit_field)
    {
        bit_field.writeRaw(bit_field_raw);
    }

    return *this;
}

//==============================================================================
BitField& BitField::operator<<=(unsigned long shift_bits)
{
    shiftLeft(shift_bits);
    return *this;
}

//==============================================================================
BitField& BitField::operator>>=(unsigned long shift_bits)
{
    shiftRight(shift_bits);
    return *this;
}

//==============================================================================
bool operator==(const BitField& lhs, const BitField& rhs)
{
    if (lhs.getLengthBits() != rhs.getLengthBits())
    {
        return false;
    }

    // We know both bit fields have equal length at this point
    unsigned long length_bits = lhs.getLengthBits();

    for (unsigned long i = 0; i < length_bits; i++)
    {
        if (lhs.getBit(i) != rhs.getBit(i))
        {
            return false;
        }
    }

    return true;
}

//==============================================================================
bool operator!=(const BitField& lhs, const BitField& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
BitField operator<<(const BitField& bit_field, unsigned long shift_bits)
{
    // Copy the bitfield then return a shifted copy
    BitField new_bit_field(bit_field);
    new_bit_field.shiftLeft(shift_bits);
    return new_bit_field;
}

//==============================================================================
BitField operator>>(const BitField& bit_field, unsigned long shift_bits)
{
    // Copy the bitfield then return a shifted copy
    BitField new_bit_field(bit_field);
    new_bit_field.shiftRight(shift_bits);
    return new_bit_field;
}
