#if !defined BIT_FIELD_HPP
#define BIT_FIELD_HPP

#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <stdexcept>
#include <string>

#include "RawDataField.hpp"

#include "misc.hpp"

// Raw binary data as a sequence of bits.  Implements RawDataField increasing
// or decreasing significance bit indexing.
class BitField : public RawDataField
{
public:

    // Dynamically allocates and maintains a bit field that is "length_bits" in
    // size.  All bits are initially unset (set to 0).  Storage is dynamically
    // allocated.
    // cppcheck-suppress noExplicitConstructor
    BitField(unsigned long length_bits);

    // Behavior depends on the value of "memory_internal".  If "memory_internal"
    // is true, the data at "buffer" of length "length_bits" will be copied
    // into dynamically-allocated memory internal to this class.  If
    // "memory_internal" is false, the data at "buffer" of length "length_bits"
    // will be used by this class in-place and no dynamic memory allocation will
    // occur.
    BitField(std::uint8_t* buffer,
             unsigned long length_bits,
             bool          memory_internal = true);

    // Copy constructor; dynamically allocates and maintains a bit field that is
    // "length_bits" in size, and then copies the given bit field into this
    // newly-allocated memory.
    BitField(const BitField& bit_field);

    // Will free the memory at "raw_bit_field" if it is owned by this class
    virtual ~BitField();

    // Reads from the "buffer" memory location plus an offset of "bit_offset"
    // bits.  No byteswapping is performed even when "source_byte_order" doesn't
    // match host byte ordering, since this is just raw data.
    virtual unsigned long readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order,
                                  unsigned long   offset_bits);

    // Writes to the "buffer" memory location plus an offset of "bit_offset"
    // bits.  No byteswapping is performed even when "source_byte_order" doesn't
    // match host byte ordering, since this is just raw data.
    virtual unsigned long writeRaw(std::uint8_t*   buffer,
                                   misc::ByteOrder destination_byte_order,
                                   unsigned long   offset_bits) const;

    // Bit access or mutation, indexed by bit
    bool getBit(unsigned long index) const;
    void setBit(unsigned long index, bool value);

    // Copies a range of bits into the given typed numeric variable.  Useful for
    // pulling things like integers and floating-point numbers out of bitfields.
    // Bit numbering follows the convention used by getBit().  Operation starts
    // by copying the least significant bit in the specified range into the
    // least significant bit in "type_var", and proceeds to successively more
    // significant bits until "count" bits are copied.
    template <class T> void getBitsAsNumericType(
        T&            type_var,
        unsigned long start_bit = 0,
        unsigned long count     = sizeof(T) * BITS_PER_BYTE) const;

    // Copies a range of bits from the given typed numeric variable.  Useful for
    // pushing things like integers and floating-point numbers into bitfields.
    // Bit numbering follows the convention used by getBit().  Operation starts
    // by copying the least significant bit in the typed numeric variable into
    // the least significant bit in the specified range, and proceeds to
    // successively more significant bits until "count" bits are copied.
    template <class T> void setBitsAsNumericType(
        T             type_var,
        unsigned long start_bit = 0,
        unsigned long count     = sizeof(T) * BITS_PER_BYTE);

    // Bits shift toward the most significant bit, if this bitfield were
    // interpreted as one big integer
    void shiftLeft(unsigned long shift_bits);

    // Bits shift toward the least significant bit, if this bitfield were
    // interpreted as one big integer
    void shiftRight(unsigned long shift_bits);

    // Returns the size of this bit field in bytes.  This will equal the number
    // of bytes written by writeRaw() and read by readRaw().
    virtual unsigned long getLengthBits() const;

    BitField& operator=(const BitField& bit_field);

    // Uses leftShift()
    BitField& operator<<=(unsigned long shift_bits);

    // Uses rightShift()
    BitField& operator>>=(unsigned long shift_bits);

private:

    unsigned int getUsedBytes() const;

    // Raw bit field is stored at this location
    std::uint8_t* bit_field_raw;

    // Raw bit field is this many bytes in length
    unsigned long length_bits;
};

//==============================================================================
inline unsigned long BitField::getLengthBits() const
{
    return static_cast<unsigned long>(length_bits);
}

//==============================================================================
inline unsigned int BitField::getUsedBytes() const
{
    return (length_bits / BITS_PER_BYTE) + 1;
}

bool operator==(const BitField& lhs, const BitField& rhs);
bool operator!=(const BitField& lhs, const BitField& rhs);

BitField operator>>(const BitField& bit_field, unsigned long shift_bits);
BitField operator<<(const BitField& bit_field, unsigned long shift_bits);

#endif
