#include <cstring>
#include <new>
#include <stdexcept>

#include "BitField.hpp"

#include "DataField.hpp"
#include "misc.hpp"

//==============================================================================
BitField::BitField(unsigned int length_bits) :
    DataField(),
    length_bits(length_bits),
    memory_internal(true)
{
    // How many bytes do we need to accomodate the requested number of bits?
    unsigned int length_bytes = (length_bits / BITS_PER_BYTE) + 1;
    bit_field_raw = new std::uint8_t[length_bytes];
    memset(bit_field_raw, 0, length_bytes);
}

//==============================================================================
BitField::BitField(std::uint8_t* buffer,
                   unsigned int  length_bits,
                   bool          memory_internal) :
    DataField(),
    length_bits(length_bits),
    memory_internal(memory_internal)
{
    if (memory_internal)
    {
        // How many bytes do we need to accomodate the requested number of bits?
        unsigned int length_bytes = (length_bits / BITS_PER_BYTE) + 1;
        bit_field_raw = new std::uint8_t[length_bytes];
        readRaw(buffer);
    }
    else
    {
        bit_field_raw = buffer;
    }
}

//==============================================================================
BitField::BitField(const BitField& bit_field) :
    DataField(),
    memory_internal(true)
{
    length_bits = bit_field.getLengthBits();

    // How many bytes do we need to accomodate the requested number of bits?
    unsigned int length_bytes = (length_bits / BITS_PER_BYTE) + 1;
    bit_field_raw = new std::uint8_t[length_bytes];

    bit_field.writeRaw(bit_field_raw);
}

//==============================================================================
BitField::~BitField()
{
    if (memory_internal)
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
    memcpy(bit_field_raw, buffer, length_bytes);
    return static_cast<unsigned long>(length_bytes) * BITS_PER_BYTE;
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
    memcpy(buffer, bit_field_raw, length_bytes);
    return static_cast<unsigned long>(length_bytes) * BITS_PER_BYTE;
}

//==============================================================================
template <class T> void BitField::getBitsAsNumericType(T&           type_var,
                                                       unsigned int start_bit,
                                                       unsigned int count) const
{
    throwIfIndexOutOfRange(start_bit);
    throwIfIndexOutOfRange(start_bit + count - 1);

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
                              sizeof(T),
                              false);

    // Copy all the bits; an alternative implementation would be to memcpy the
    // relevant data over, shift down and then mask out the irrelevant bits
    for (unsigned int i = 0; i < count; ++i)
    {
        working_bitfield.setBit(i, getBit(start_bit + i));
    }
}

// Use this macro to instantiate getBitsAsNumericType() for all the intrinsic
// numeric types.  "char" is arguably not a numeric type but let's include it
// since it's sometimes useful to use it as if it were a numeric type
#define INSTANTIATE_GETBITSASNUMERICTYPE(Type)                          \
    template void                                                       \
    BitField::getBitsAsNumericType(Type&, unsigned int, unsigned int) const;

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
template <class T>
void BitField::setBitsAsNumericType(T            type_var,
                                    unsigned int start_bit,
                                    unsigned int count)
{
    throwIfIndexOutOfRange(start_bit);
    throwIfIndexOutOfRange(start_bit + count - 1);

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
    for (unsigned int i = 0; i < count; ++i)
    {
       setBit(start_bit + i, working_bitfield.getBit(i));
    }
}

// Use this macro to instantiate setBitsAsNumericType() for all the intrinsic
// numeric types.  "char" is arguably not a numeric type but let's include it
// since it's sometimes useful to use it as if it were a numeric type
#define INSTANTIATE_SETBITSASNUMERICTYPE(Type)                          \
    template void                                                       \
    BitField::setBitsAsNumericType(Type, unsigned int, unsigned int);

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
void BitField::shiftLeft(unsigned int shift_bits)
{
    unsigned int bit_field_bits = getLengthBits();

    if (shift_bits >= bit_field_bits)
    {
        throw std::runtime_error(
            "Requested shift amount must be less than the width of the field");
    }

    // A shift of 0 bits is a no-op
    if (shift_bits == 0)
    {
        return;
    }

    for (unsigned int i = bit_field_bits - 1; i != shift_bits - 1; --i)
    {
        setBit(i, getBit(i - shift_bits));
    }

    // Shift in zeros
    for (unsigned int i = shift_bits - 1; i != 0; --i)
    {
        setBit(i, false);
    }

    // Least significant bit will always be 0
    setBit(0, false);
}

//==============================================================================
void BitField::shiftRight(unsigned int shift_bits)
{
    unsigned int bit_field_bits = getLengthBits();

    if (shift_bits >= bit_field_bits)
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
    for (unsigned int i = 0; i < bit_field_bits - shift_bits; i++)
    {
        setBit(i, getBit(i + shift_bits));
    }

    // Shift in zeros
    for (unsigned int i = bit_field_bits - shift_bits; i < bit_field_bits; i++)
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
BitField& BitField::operator<<=(unsigned int shift_bits)
{
    shiftLeft(shift_bits);
    return *this;
}

//==============================================================================
BitField& BitField::operator>>=(unsigned int shift_bits)
{
    shiftRight(shift_bits);
    return *this;
}

//==============================================================================
bool operator==(const BitField& bit_field1, const BitField& bit_field2)
{
    if (bit_field1.getLengthBits() != bit_field2.getLengthBits())
    {
        return false;
    }

    // We know both bit fields have equal length at this point
    unsigned int length_bits = bit_field1.getLengthBits();

    for (unsigned int i = 0; i < length_bits; i++)
    {
        if (bit_field1.getBit(i) != bit_field2.getBit(i))
        {
            return false;
        }
    }

    return true;
}

//==============================================================================
bool operator!=(const BitField& bit_field1, const BitField& bit_field2)
{
    return !(bit_field1 == bit_field2);
}

//==============================================================================
BitField operator<<(const BitField& bit_field, unsigned int shift_bits)
{
    // Copy the bitfield then return a shifted copy
    BitField new_bit_field(bit_field);
    new_bit_field.shiftLeft(shift_bits);
    return new_bit_field;
}

//==============================================================================
BitField operator>>(const BitField& bit_field, unsigned int shift_bits)
{
    // Copy the bitfield then return a shifted copy
    BitField new_bit_field(bit_field);
    new_bit_field.shiftRight(shift_bits);
    return new_bit_field;
}
