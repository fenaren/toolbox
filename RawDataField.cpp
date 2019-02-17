#include <stdexcept>
#include <cstring>
#include <new>

#include "RawDataField.hpp"

#include "DataField.hpp"
#include "misc.hpp"

//==============================================================================
RawDataField::RawDataField(unsigned int length_bytes) :
    DataField(),
    memory_internal(true),
    length_bytes(length_bytes)
{
    bit_field_raw = new std::uint8_t[length_bytes];
    memset(bit_field_raw, 0, length_bytes);
}

//==============================================================================
RawDataField::RawDataField(std::uint8_t* buffer,
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
RawDataField::RawDataField(const RawDataField& bit_field) :
    DataField(),
    memory_internal(true)
{
    length_bytes = bit_field.getLengthBytes();

    bit_field_raw = new std::uint8_t[length_bytes];

    bit_field.writeRaw(bit_field_raw);
}

//==============================================================================
RawDataField::~RawDataField()
{
    if (memory_internal)
    {
        delete[] bit_field_raw;
    }
}

//==============================================================================
unsigned int RawDataField::readRaw(const std::uint8_t* buffer)
{
    return DataField::readRaw(buffer);
}

//==============================================================================
unsigned int RawDataField::readRaw(const std::uint8_t* buffer,
                               misc::ByteOrder     source_byte_order)
{
    // No byteswapping regardless of "source_byte_order" setting
    memcpy(bit_field_raw, buffer, length_bytes);
    return length_bytes;
}

//==============================================================================
unsigned int RawDataField::writeRaw(std::uint8_t* buffer) const
{
    return DataField::writeRaw(buffer);
}

//==============================================================================
unsigned int RawDataField::writeRaw(std::uint8_t*   buffer,
                                misc::ByteOrder destination_byte_order) const
{
    // No byteswapping regardless of "destination_byte_order" setting
    memcpy(buffer, bit_field_raw, length_bytes);
    return length_bytes;
}

//==============================================================================
template <class T> void RawDataField::getBitsAsNumericType(T&           type_var,
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
    RawDataField working_bitfield(reinterpret_cast<std::uint8_t*>(&type_var),
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
    RawDataField::getBitsAsNumericType(Type&, unsigned int, unsigned int) const;

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
void RawDataField::setBitsAsNumericType(T            type_var,
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
    RawDataField working_bitfield(reinterpret_cast<std::uint8_t*>(&type_var),
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
    RawDataField::setBitsAsNumericType(Type, unsigned int, unsigned int);

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
void RawDataField::shiftLeft(unsigned int shift_bits)
{
    unsigned int bit_field_bits = getLengthBytes() * RawDataField::BITS_PER_BYTE;

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
void RawDataField::shiftRight(unsigned int shift_bits)
{
    unsigned int bit_field_bits = getLengthBytes() * RawDataField::BITS_PER_BYTE;

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
RawDataField& RawDataField::operator=(const RawDataField& bit_field)
{
    if (this != &bit_field)
    {
        bit_field.writeRaw(bit_field_raw);
    }

    return *this;
}

//==============================================================================
RawDataField& RawDataField::operator<<=(unsigned int shift_bits)
{
    shiftLeft(shift_bits);
    return *this;
}

//==============================================================================
RawDataField& RawDataField::operator>>=(unsigned int shift_bits)
{
    shiftRight(shift_bits);
    return *this;
}

//==============================================================================
bool operator==(const RawDataField& bit_field1, const RawDataField& bit_field2)
{
    if (bit_field1.getLengthBytes() != bit_field2.getLengthBytes())
    {
        return false;
    }

    // We know both bit fields have equal length at this point
    unsigned int length_bytes = bit_field1.getLengthBytes();

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
bool operator!=(const RawDataField& bit_field1, const RawDataField& bit_field2)
{
    return !(bit_field1 == bit_field2);
}

//==============================================================================
RawDataField operator<<(const RawDataField& bit_field, unsigned int shift_bits)
{
    // Copy the bitfield then return a shifted copy
    RawDataField new_bit_field(bit_field);
    new_bit_field.shiftLeft(shift_bits);
    return new_bit_field;
}

//==============================================================================
RawDataField operator>>(const RawDataField& bit_field, unsigned int shift_bits)
{
    // Copy the bitfield then return a shifted copy
    RawDataField new_bit_field(bit_field);
    new_bit_field.shiftRight(shift_bits);
    return new_bit_field;
}
