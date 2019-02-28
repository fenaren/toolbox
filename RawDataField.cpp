#include <cmath>
#include <cstring>
#include <new>
#include <stdexcept>

#include "RawDataField.hpp"

#include "DataField.hpp"
#include "misc.hpp"

//==============================================================================
RawDataField::RawDataField(unsigned long   length,
                           misc::DataUnits length_units,
                           IndexingMode    bit_indexing_mode) :
    RawDataField(length, length_units, true, bit_indexing_mode)
{
}

//==============================================================================
RawDataField::RawDataField(std::uint8_t*   buffer,
                           unsigned long   length,
                           misc::DataUnits length_units,
                           bool            memory_internal,
                           IndexingMode    bit_indexing_mode) :
    RawDataField(length, length_units, memory_internal, bit_indexing_mode)
{
    // Delegate RawDataField constructor has already set up our "raw_data"
    // pointer.  At this point we can just start using it.

    if (memory_internal)
    {
        DataField::readRaw(buffer);
    }
    else
    {
        raw_data = buffer;
    }
}

//==============================================================================
// cppcheck-suppress uninitMemberVar
RawDataField::RawDataField(const RawDataField& raw_data_field) :
    RawDataField(raw_data_field.getLengthBits(),
                 misc::BITS,
                 true,
                 raw_data_field.getBitIndexingMode())
{
    // Delegate RawDataField constructor has already set up our "raw_data"
    // pointer.  At this point we can just start using it.
    raw_data_field.DataField::writeRaw(raw_data);
}

//==============================================================================
RawDataField::RawDataField(unsigned long   length,
                           misc::DataUnits length_units,
                           bool            memory_internal,
                           IndexingMode    bit_indexing_mode) :
    DataField(),
    memory_internal(memory_internal),
    bit_indexing_mode(bit_indexing_mode)
{
    // Set length_bits appropriately
    if (length_units == misc::BYTES)
    {
        length_bits = length * BITS_PER_BYTE;
    }
    else if (length_units == misc::BITS)
    {
        length_bits = length;
    }
    else
    {
        std::runtime_error("Unsupported units type specified");
    }

    if (memory_internal)
    {
        // We're managing memory internally so we need some memory.  Memory
        // amount calculation is copied from the getLengthBytes definition in
        // DataField.  We don't use that directly here since getLengthBytes will
        // call getLengthBits on this class, and this class isn't fully
        // instantiated yet.
        raw_data = new std::uint8_t[static_cast<unsigned int>(
                std::ceil(static_cast<double>(length_bits) /
                          static_cast<double>(BITS_PER_BYTE)))];
    }
}

//==============================================================================
RawDataField::~RawDataField()
{
    if (memory_internal)
    {
        delete[] raw_data;
    }
}

//==============================================================================
unsigned long RawDataField::readRaw(std::uint8_t*   buffer,
                                    misc::ByteOrder source_byte_order)
{
    // No byteswapping regardless of "source_byte_order" setting
    memcpy(raw_data, buffer, getLengthBytes());
    return length_bits;
}

//==============================================================================
unsigned long RawDataField::writeRaw(
    std::uint8_t*   buffer,
    misc::ByteOrder destination_byte_order) const
{
    // No byteswapping regardless of "destination_byte_order" setting
    memcpy(buffer, raw_data, getLengthBytes());
    return length_bits;
}

//==============================================================================
std::uint8_t RawDataField::getByte(unsigned int index) const
{
    throwIfIndexOutOfRange(index, getLengthBytes());
    return raw_data[index];
}

//==============================================================================
void RawDataField::setByte(unsigned int index, std::uint8_t value)
{
    throwIfIndexOutOfRange(index, getLengthBytes());
    raw_data[index] = value;
}

//==============================================================================
bool RawDataField::getBit(unsigned long index) const
{
    throwIfIndexOutOfRange(index, length_bits);

    // This returns the index of the byte we want and the index of the bit
    // within that byte
    std::ldiv_t div_result = std::ldiv(index, BITS_PER_BYTE);

    // This is the byte containing the bit we want
    std::uint8_t target_byte = raw_data[div_result.quot];

    // We still need to find the right bit, div_result.rem has the index.  Shift
    // the bit we want down to the least significant bit and then mask out the
    // other bits
    if (bit_indexing_mode == LS_LEAST)
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
void RawDataField::setBit(unsigned long index, bool value)
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

    // Shift the bit we set above to the correct position depending on bit
    // indexing setting
    unsigned int shift_amount = div_result.rem;
    if (bit_indexing_mode == MS_LEAST)
    {
        shift_amount = BITS_PER_BYTE - div_result.rem - 1;
    }
    target_byte <<= shift_amount;

    // Shift the mask into the right place as well
    mask <<= shift_amount;

    // We have the byte and mask shifted properly, now we just have to write the
    // byte into the proper place in raw_bit_field without disturbing the other
    // bits

    unsigned int byte_index = div_result.quot;

    // Mask the bit setting in
    raw_data[byte_index] &= ~mask;
    raw_data[byte_index] |= target_byte;
}

//==============================================================================
template <class T>
void RawDataField::getBitsAsNumericType(T&           type_var,
                                        unsigned int start_bit,
                                        unsigned int count) const
{
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

    // Use the given variable as if it were just raw data, and set bits inside
    // it
    RawDataField working_rdf(reinterpret_cast<std::uint8_t*>(&type_var),
                             sizeof(T),
                             misc::BYTES,
                             false,
                             bit_indexing_mode);

    // Copy all the bits; an alternative implementation would be to memcpy the
    // relevant data over, shift down and then mask out the irrelevant bits, but
    // this uses the getBit() and setBit() functions which account for bit
    // indexing mode us.
    for (unsigned int i = 0; i < count; ++i)
    {
        working_rdf.setBit(i, getBit(start_bit + i));
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
    // Handle bad input
    if (start_bit >= length_bits || start_bit + count > length_bits)
    {
        throw std::out_of_range("Out-of-range bit(s) specified");
    }
    else if (count > sizeof(T) * BITS_PER_BYTE)
    {
        throw std::out_of_range("Not enough bits in the source type");
    }

    // Use the given variable as if it were raw data, and set bits inside it
    RawDataField working_rdf(reinterpret_cast<std::uint8_t*>(&type_var),
                             sizeof(T),
                             misc::BYTES,
                             false,
                             bit_indexing_mode);

    // Copy all the bits; an alternative implementation would be to memcpy the
    // relevant data over, shift down and then mask out the irrelevant bits
    for (unsigned int i = 0; i < count; ++i)
    {
        setBit(start_bit + i, working_rdf.getBit(i));
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

    for (unsigned int i = length_bits - 1; i != shift_bits - 1; --i)
    {
        setBit(i, getBit(i - shift_bits));
    }

    // Shift in zeros
    for (unsigned int i = shift_bits - 1; i != 0; --i)
    {
        setBit(i, false);
    }

    // Bit 0 will always be unset.  Ideally this would be done in the loop above
    // but because we're looping down we have to stop that loop one short
    setBit(0, false);
}

//==============================================================================
void RawDataField::shiftRight(unsigned int shift_bits)
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
    for (unsigned int i = 0; i < length_bits - shift_bits; i++)
    {
        setBit(i, getBit(i + shift_bits));
    }

    // Shift in zeros
    for (unsigned int i = length_bits - shift_bits; i < length_bits; i++)
    {
        setBit(i, false);
    }
}

//==============================================================================
RawDataField& RawDataField::operator=(const RawDataField& raw_data_field)
{
    if (this != &raw_data_field)
    {
        raw_data_field.DataField::writeRaw(raw_data);
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
bool operator==(const RawDataField& lhs, const RawDataField& rhs)
{
    if (lhs.getLengthBits() != rhs.getLengthBits())
    {
        return false;
    }

    // We know both raw data fields have equal length at this point
    unsigned int length_bits = lhs.getLengthBits();

    for (unsigned int i = 0; i < length_bits; i++)
    {
        if (lhs.getBit(i) != rhs.getBit(i))
        {
            return false;
        }
    }

    return true;
}

//==============================================================================
bool operator!=(const RawDataField& lhs, const RawDataField& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
RawDataField operator<<(const RawDataField& lhs, unsigned int rhs)
{
    // Copy then return a shifted copy
    RawDataField new_raw_data_field(lhs);
    new_raw_data_field.shiftLeft(rhs);
    return new_raw_data_field;
}

//==============================================================================
RawDataField operator>>(const RawDataField& lhs, unsigned int rhs)
{
    // Copy then return a shifted copy
    RawDataField new_raw_data_field(lhs);
    new_raw_data_field.shiftRight(rhs);
    return new_raw_data_field;
}
