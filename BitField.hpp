#if !defined BIT_FIELD_HPP
#define BIT_FIELD_HPP

#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <stdexcept>
#include <string>

#include "DataField.hpp"

#include "misc.hpp"

class BitField : public DataField
{
public:

    enum IndexingMode
    {
        MS_ZERO,
        LS_ZERO
    };

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

    // Reads a raw bit field from the "buffer" memory location.  Byte ordering
    // has no relevance to bit fields so no byte swapping is performed.
    virtual unsigned long readRaw(std::uint8_t* buffer,
                                  unsigned long offset_bits = 0);

    // Reads a raw bit field from the "buffer" memory location.  This
    // function is required by the framework to be implemented here, despite
    // being functionally identical to the single-argument version defined
    // above.  If byte ordering were relevant to bit fields (in the
    // general sense of the term) this function would be where that difference
    // would be handled.
    virtual unsigned long readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order,
                                  unsigned long   offset_bits = 0);

    // Writes this bit field to the "buffer" memory location.  Byte ordering has
    // no relevance to bit fields so no byte swapping is performed.
    virtual unsigned long writeRaw(std::uint8_t* buffer,
                                   unsigned long offset_bits = 0) const;

    // Writes this bit field to the "buffer" memory location.  This function is
    // required by the framework to be implemented here, despite being
    // functionally identical to the single-argument version defined above.  If
    // byte ordering were relevant to bit fields (in the general sense of the
    // term) this function would be where that difference would be handled.
    virtual unsigned long writeRaw(std::uint8_t*   buffer,
                                   misc::ByteOrder destination_byte_order,
                                   unsigned long   offset_bits = 0) const;

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

    // Simple accessor for memory_internal
    bool getMemoryInternal() const;

    IndexingMode getBitIndexingMode() const;
    void setBitIndexingMode(IndexingMode im);

    IndexingMode getByteIndexingMode() const;
    void setByteIndexingMode(IndexingMode im);

    BitField& operator=(const BitField& bit_field);

    // Uses leftShift()
    BitField& operator<<=(unsigned long shift_bits);

    // Uses rightShift()
    BitField& operator>>=(unsigned long shift_bits);

private:

    // Tosses a std::out_of_range exception if octet >= length_bits
    void throwIfIndexOutOfRange(unsigned long index) const;

    unsigned int getUsedBytes() const;

    // Raw bit field is stored at this location
    std::uint8_t* bit_field_raw;

    // Raw bit field is this many bytes in length
    unsigned long length_bits;

    // Does this class own the memory at "bit_field_raw"?
    bool memory_internal;

    // Defaults for indexing modes for bits and bytes
    IndexingMode im_bytes;
    IndexingMode im_bits;
};

//==============================================================================
inline unsigned long BitField::getLengthBits() const
{
    return static_cast<unsigned long>(length_bits);
}

//==============================================================================
inline BitField::IndexingMode BitField::getBitIndexingMode() const
{
    return im_bits;
}

//==============================================================================
inline void BitField::setBitIndexingMode(BitField::IndexingMode im)
{
    im_bits = im;
}

//==============================================================================
inline BitField::IndexingMode BitField::getByteIndexingMode() const
{
    return im_bytes;
}

//==============================================================================
inline void BitField::setByteIndexingMode(BitField::IndexingMode im)
{
    im_bytes = im;
}

//==============================================================================
inline bool BitField::getMemoryInternal() const
{
    return memory_internal;
}

//==============================================================================
inline void BitField::throwIfIndexOutOfRange(unsigned long index) const
{
    if (index >= length_bits)
    {
        throw std::out_of_range("Bit index out of range");
    }
}

//==============================================================================
inline unsigned int BitField::getUsedBytes() const
{
    return (length_bits / BITS_PER_BYTE) + 1;
}

bool operator==(const BitField& bit_field1, const BitField& bit_field2);
bool operator!=(const BitField& bit_field1, const BitField& bit_field2);

BitField operator>>(const BitField& bit_field, unsigned long shift_bits);
BitField operator<<(const BitField& bit_field, unsigned long shift_bits);

#endif
