#include <stdexcept>
#include <cstring>
#include <new>

#include "BitField.hpp"

#include "DataField.hpp"
#include "misc.hpp"

//==============================================================================
// Dynamically allocates and maintains a bit field that is "length_bytes" in
// size.  All bits are initially unset (set to 0).  Storage is dynamically
// allocated.
//==============================================================================
BitField::BitField(unsigned int length_bytes) :
    DataField(),
    memory_internal(true),
    length_bytes(length_bytes)
{
    bit_field_raw = new std::uint8_t[length_bytes];
    memset(bit_field_raw, 0, length_bytes);
}

//==============================================================================
// Behavior depends on the value of "memory_internal".  If "memory_internal" is
// true, the data at "buffer" of length "length_bytes" will be copied into
// dynamically-allocated memory internal to this class.  If "memory_internal" is
// false, the data at "buffer" of length "length_bytes" will be used by this
// class in-place and no dynamic memory allocation will occur.
//==============================================================================
BitField::BitField(std::uint8_t* buffer,
                   unsigned int  length_bytes,
                   bool          memory_internal) :
    DataField(),
    memory_internal(memory_internal),
    length_bytes(length_bytes)
{
    if (memory_internal)
    {
        bit_field_raw = new std::uint8_t[length_bytes];
        readRaw(buffer);
    }
    else
    {
        bit_field_raw = buffer;
    }
}

//==============================================================================
// Copy constructor; dynamically allocates and maintains a bit field that is
// "length_bytes" in size, and then copies the given bit field into this
// newly-allocated memory.
//==============================================================================
BitField::BitField(const BitField& bit_field) :
    DataField(),
    memory_internal(true)
{
    length_bytes = bit_field.getLengthBits();

    bit_field_raw = new std::uint8_t[length_bytes];

    bit_field.writeRaw(bit_field_raw);
}

//==============================================================================
// Frees the memory at "bit_field_raw" if owned by this class
//==============================================================================
BitField::~BitField()
{
    if (memory_internal)
    {
        delete[] bit_field_raw;
    }
}

//==============================================================================
// Reads a raw bit field from the "buffer" memory location.  Byte ordering has
// no relevance to bit fields so no byte swapping is performed.
//==============================================================================
unsigned long BitField::readRaw(const std::uint8_t* buffer,
                                unsigned int        offset_bits)
{
    return DataField::readRaw(buffer, offset_bits);
}

//==============================================================================
// Reads a raw bit field from the "buffer" memory location.  This function is
// required by the framework to be implemented here, despite being functionally
// identical to the single-argument version defined above.  If byte ordering
// were relevant to bit fields (in the general sense of the term) this function
// would be where that difference would be handled.
//==============================================================================
unsigned long BitField::readRaw(const std::uint8_t* buffer,
                                misc::ByteOrder     source_byte_order,
                                unsigned int        offset_bits)
{
    // No byteswapping regardless of "source_byte_order" setting
    memcpy(bit_field_raw, buffer, length_bytes);
    return length_bytes;
}

//==============================================================================
// Writes this bit field to the "buffer" memory location.  Byte ordering has no
// relevance to bit fields so no byte swapping is performed.
//==============================================================================
unsigned long BitField::writeRaw(std::uint8_t* buffer,
                                 unsigned int  offset_bits) const
{
    return DataField::writeRaw(buffer, offset_bits);
}

//==============================================================================
// Writes this bit field to the "buffer" memory location.  This function is
// required by the framework to be implemented here, despite being functionally
// identical to the single-argument version defined above.  If byte ordering
// were relevant to bit fields (in the general sense of the term) this function
// would be where that difference would be handled.
//==============================================================================
unsigned long BitField::writeRaw(std::uint8_t*   buffer,
                                 misc::ByteOrder destination_byte_order,
                                 unsigned int    offset_bits) const
{
    // No byteswapping regardless of "destination_byte_order" setting
    memcpy(buffer, bit_field_raw, length_bytes);
    return length_bytes;
}

//==============================================================================
// Copies a range of bits into the given typed numeric variable.  Useful for
// pulling things like integers and floating-point numbers out of bitfields.
// Bit numbering follows the convention used by getBit().  Operation starts by
// copying the least significant bit in the specified range into the least
// significant bit in "type_var", and proceeds to successively more significant
// bits until "count" bits are copied.
//==============================================================================
template <class T> void BitField::getBitsAsNumericType(T&           type_var,
                                                       unsigned int start_bit,
                                                       unsigned int count) const
{
    unsigned int length_bits = length_bytes * BITS_PER_BYTE;

    // Handle bad input
    if (start_bit >= length_bits || start_bit + count > length_bits)
    {
        throw std::out_of_range("Out-of-range bit(s) specified");
    }
    else if (count > sizeof(T) * BITS_PER_BYTE)
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
// Copies a range of bits from the given typed numeric variable.  Useful for
// pushing things like integers and floating-point numbers into bitfields.  Bit
// numbering follows the convention used by getBit().  Operation starts by
// copying the least significant bit in the typed numeric variable into the
// least significant bit in the specified range, and proceeds to successively
// more significant bits until "count" bits are copied.
//==============================================================================
template <class T>
void BitField::setBitsAsNumericType(T            type_var,
                                    unsigned int start_bit,
                                    unsigned int count)
{
    unsigned int length_bits = length_bytes * BITS_PER_BYTE;

    // Handle bad input
    if (start_bit >= length_bits || start_bit + count > length_bits)
    {
        throw std::out_of_range("Out-of-range bit(s) specified");
    }
    else if (count > sizeof(T) * BITS_PER_BYTE)
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
// Bits shift toward the most significant bit, if this bitfield were
// interpreted as one big integer
//==============================================================================
void BitField::shiftLeft(unsigned int shift_bits)
{
    unsigned int bit_field_bits = getLengthBits() * BITS_PER_BYTE;

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
// Bits shift toward the least significant bit, if this bitfield were
// interpreted as one big integer
//==============================================================================
void BitField::shiftRight(unsigned int shift_bits)
{
    unsigned int bit_field_bits = getLengthBits() * BITS_PER_BYTE;

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
// Assigns a BitField to this BitField
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
// Uses leftShift()
//==============================================================================
BitField& BitField::operator<<=(unsigned int shift_bits)
{
    shiftLeft(shift_bits);
    return *this;
}

//==============================================================================
// Uses rightShift()
//==============================================================================
BitField& BitField::operator>>=(unsigned int shift_bits)
{
    shiftRight(shift_bits);
    return *this;
}

//==============================================================================
// Equality comparison, BitField == BitField
//==============================================================================
bool operator==(const BitField& bit_field1, const BitField& bit_field2)
{
    if (bit_field1.getLengthBits() != bit_field2.getLengthBits())
    {
        return false;
    }

    // We know both bit fields have equal length at this point
    unsigned int length_bytes = bit_field1.getLengthBits();

    for (unsigned int i = 0; i < length_bytes; i++)
    {
        if (bit_field1.getOctet(i) != bit_field2.getOctet(i))
        {
            return false;
        }
    }

    return true;
}

//==============================================================================
// Inequality comparison, BitField != BitField
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
