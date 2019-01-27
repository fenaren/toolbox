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
        MS_FIRST,
        LS_FIRST
    };

    // Dynamically allocates and maintains a bit field that is "length_bits" in
    // size.  All bits are initially unset (set to 0).  Storage is dynamically
    // allocated.
    // cppcheck-suppress noExplicitConstructor
    BitField(unsigned int length_bits);

    // Behavior depends on the value of "memory_internal".  If "memory_internal"
    // is true, the data at "buffer" of length "length_bits" will be copied
    // into dynamically-allocated memory internal to this class.  If
    // "memory_internal" is false, the data at "buffer" of length "length_bits"
    // will be used by this class in-place and no dynamic memory allocation will
    // occur.
    BitField(std::uint8_t* buffer,
             unsigned int  length_bits,
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

    // Octets are indexed starting from 0 for the byte at the lowest memory
    // address and increasing to the highest memory address

    // Bits are indexed starting with 0 for the least significant bit and
    // increasing to the most significant bit

    // Octet access or mutation, indexed by (obviously) octet
    //std::uint8_t getOctet(unsigned int octet) const;
    //void setOctet(unsigned int octet, std::uint8_t value);

    // Bit access or mutation, indexed by octet and the bit within that octet
    //bool getBit(unsigned int octet, unsigned int octet_bit) const;
    //void setBit(unsigned int octet, unsigned int octet_bit, bool value);

    // Bit access or mutation, indexed by bit
    bool getBit(unsigned int bit) const;
    void setBit(unsigned int bit, bool value);

    // Copies a range of bits into the given typed numeric variable.  Useful for
    // pulling things like integers and floating-point numbers out of bitfields.
    // Bit numbering follows the convention used by getBit().  Operation starts
    // by copying the least significant bit in the specified range into the
    // least significant bit in "type_var", and proceeds to successively more
    // significant bits until "count" bits are copied.
    template <class T> void getBitsAsNumericType(
        T&           type_var,
        unsigned int start_bit = 0,
        unsigned int count     = sizeof(T) * BITS_PER_BYTE) const;

    // Copies a range of bits from the given typed numeric variable.  Useful for
    // pushing things like integers and floating-point numbers into bitfields.
    // Bit numbering follows the convention used by getBit().  Operation starts
    // by copying the least significant bit in the typed numeric variable into
    // the least significant bit in the specified range, and proceeds to
    // successively more significant bits until "count" bits are copied.
    template <class T> void setBitsAsNumericType(
        T            type_var,
        unsigned int start_bit = 0,
        unsigned int count     = sizeof(T) * BITS_PER_BYTE);

    // Bits shift toward the most significant bit, if this bitfield were
    // interpreted as one big integer
    void shiftLeft(unsigned int shift_bits);

    // Bits shift toward the least significant bit, if this bitfield were
    // interpreted as one big integer
    void shiftRight(unsigned int shift_bits);

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
    BitField& operator<<=(unsigned int shift_bits);

    // Uses rightShift()
    BitField& operator>>=(unsigned int shift_bits);

private:

    // Tosses a std::out_of_range exception if octet >= length_bits
    void throwIfIndexOutOfRange(unsigned int octet) const;

    // Raw bit field is stored at this location
    std::uint8_t* bit_field_raw;

    // Raw bit field is this many bytes in length
    unsigned int length_bits;

    // Does this class own the memory at "bit_field_raw"?
    bool memory_internal;

    // Defaults for indexing modes for bits and bytes
    IndexingMode im_bits;
    IndexingMode im_bytes;
};

//==============================================================================
/*inline std::uint8_t BitField::getOctet(unsigned int octet) const
{
    throwIfIndexOutOfRange(octet);
    return bit_field_raw[octet];
    }*/

//==============================================================================
/*inline void BitField::setOctet(unsigned int octet, std::uint8_t value)
{
    throwIfIndexOutOfRange(octet);
    bit_field_raw[octet] = value;
    }*/

//==============================================================================
/*inline bool BitField::getBit(unsigned int octet, unsigned int octet_bit) const
{
    throwIfIndexOutOfRange(octet);

    return working_octet.test(octet_bit);
    }*/

//==============================================================================
inline bool BitField::getBit(unsigned int bit) const
{
    throwIfIndexOutOfRange(bit);

    // This returns the index of the byte we want and the index of the bit
    // within that byte
    std::ldiv_t div_result = std::ldiv(bit, BITS_PER_BYTE);

    return getBit(std::floor(bit / BITS_PER_BYTE), bit % BITS_PER_BYTE);
}

//==============================================================================
/*inline
void BitField::setBit(unsigned int octet, unsigned int octet_bit, bool value)
{
    throwIfIndexOutOfRange(octet);

    // Use std::bitset to do the bitshifting nonsense for us
    std::bitset<BITS_PER_BYTE> working_octet(bit_field_raw[octet]);
    working_octet.set(octet_bit, value);
    bit_field_raw[octet] = static_cast<std::uint8_t>(working_octet.to_ulong());
    }*/

//==============================================================================
inline void BitField::setBit(unsigned int bit, bool value)
{
    throwIfIndexOutOfRange(bit);
    
    setBit(std::floor(bit / BITS_PER_BYTE), bit % BITS_PER_BYTE, value);
}

//==============================================================================
inline unsigned long BitField::getLengthBits() const
{
    return static_cast<unsigned long>(length_bits);
}

//==============================================================================
BitField::IndexingMode BitField::getBitIndexingMode() const
{
    return im_bits;
}

//==============================================================================
void BitField::setBitIndexingMode(BitField::IndexingMode im)
{
    im_bits = im;
}

//==============================================================================
BitField::IndexingMode BitField::getByteIndexingMode() const
{
    return im_bytes;
}

//==============================================================================
void BitField::setByteIndexingMode(BitField::IndexingMode im)
{
    im_bytes = im;
}

//==============================================================================
inline bool BitField::getMemoryInternal() const
{
    return memory_internal;
}

//==============================================================================
inline void BitField::throwIfIndexOutOfRange(unsigned int index) const
{
    if (index >= length_bits)
    {
        throw std::out_of_range("Out-of-range bits");
    }
}

bool operator==(const BitField& bit_field1, const BitField& bit_field2);
bool operator!=(const BitField& bit_field1, const BitField& bit_field2);

BitField operator>>(const BitField& bit_field, unsigned int shift_bits);
BitField operator<<(const BitField& bit_field, unsigned int shift_bits);

#endif
