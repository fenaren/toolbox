#if !defined RAW_DATA_FIELD_HPP
#define RAW_DATA_FIELD_HPP

#include <bitset>
#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <string>

#include "DataField.hpp"

#include "misc.hpp"

class RawDataField : public DataField
{
public:

    // Dynamically allocates and maintains data field of size "length".  Units
    // of length are specified in "length_units".  Storage is dynamically
    // allocated.
    // cppcheck-suppress noExplicitConstructor
    RawDataField(unsigned long          length,
                 misc::DataUnits        length_units,
                 misc::DataIndexingMode indexing_mode);

    // Behavior depends on the value of "memory_internal".  If "memory_internal"
    // is true, the data at "buffer" of will be copied into dynamically
    // allocated memory internal to this class.  If "memory_internal" is false,
    // the data at "buffer" will be used by this class in-place and no dynamic
    // memory allocation will occur.
    RawDataField(std::uint8_t*          buffer,
                 unsigned long          length,
                 misc::DataUnits        length_units,
                 misc::DataIndexingMode indexing_mode,
                 bool                   memory_internal = true);

    // Copy constructor; dynamically allocates and maintains a bit field that is
    // "length_bytes" in size, and then copies the given bit field into this
    // newly-allocated memory.
    RawDataField(const RawDataField& bit_field);

    // Will free the memory at "raw_bit_field" if it is owned by this class
    virtual ~RawDataField();

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

    // Octets are indexed starting from 0 for the byte at the lowest memory
    // address and increasing to the highest memory address

    // Bits are indexed starting with 0 for the least significant bit and
    // increasing to the most significant bit

    // Octet access or mutation, indexed by (obviously) octet
    std::uint8_t getByte(unsigned int octet) const;
    void setByte(unsigned int octet, std::uint8_t value);

    // Bit access or mutation, indexed by octet and the bit within that octet
    bool getBit(unsigned int octet, unsigned int octet_bit) const;
    void setBit(unsigned int octet, unsigned int octet_bit, bool value);

    // Bit access or mutation, indexed by bit
    bool getBit(unsigned long bit) const;
    void setBit(unsigned long bit, bool value);

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

    // Returns the size of this field in bits.  This will equal the number of
    // bits written by writeRaw() and read by readRaw().
    virtual unsigned long getLengthBits() const;

    // Simple accessor for memory_internal
    bool getMemoryInternal() const;

    // Indexing mode access
    misc::DataIndexingMode getIndexingMode() const;

    // Indexing mode mutator
    void setIndexingMode(misc::DataIndexingMode indexing_mode);

    RawDataField& operator=(const RawDataField& bit_field);

    // Uses leftShift()
    RawDataField& operator<<=(unsigned int shift_bits);

    // Uses rightShift()
    RawDataField& operator>>=(unsigned int shift_bits);

private:

    // Tosses a std::out_of_range exception if index >= size
    void throwIfIndexOutOfRange(unsigned long index, unsigned long size) const;

    // Raw bit field is stored at this location
    std::uint8_t* raw_data;

    // Raw bit field is this many bytes in length
    unsigned int length_bytes;

    // Does this class own the memory at "raw_data"?
    bool memory_internal;

    misc::DataIndexingMode indexing_mode;
};

//==============================================================================
inline std::uint8_t RawDataField::getByte(unsigned int index) const
{
    throwIfIndexOutOfRange(index, getLengthBytes());

    unsigned long real_index = index;

    if (indexing_mode == misc::LS_ZERO)
    {
        real_index = length_bytes - index - 1;
    }

    return raw_data[real_index];
}

//==============================================================================
inline void RawDataField::setByte(unsigned int index, std::uint8_t value)
{
    throwIfIndexOutOfRange(index);
    raw_data[index] = value;
}

//==============================================================================
inline
bool RawDataField::getBit(unsigned int index, unsigned int octet_bit) const
{
    throwIfIndexOutOfRange(index);

    // Use std::bitset to do the bitshifting nonsense for us
    std::bitset<BITS_PER_BYTE> working_octet(raw_data[index]);
    return working_octet.test(octet_bit);
}

//==============================================================================
inline bool RawDataField::getBit(unsigned int bit) const
{
    return getBit(std::floor(bit / BITS_PER_BYTE), bit % BITS_PER_BYTE);
}

//==============================================================================
inline void
RawDataField::setBit(unsigned int index, unsigned int octet_bit, bool value)
{
    throwIfIndexOutOfRange(index);

    // Use std::bitset to do the bitshifting nonsense for us
    std::bitset<BITS_PER_BYTE> working_octet(raw_data[index]);
    working_octet.set(octet_bit, value);
    raw_data[index] = static_cast<std::uint8_t>(working_octet.to_ulong());
}

//==============================================================================
inline void RawDataField::setBit(unsigned int bit, bool value)
{
    setBit(std::floor(bit / BITS_PER_BYTE), bit % BITS_PER_BYTE, value);
}

//==============================================================================
inline bool RawDataField::getMemoryInternal() const
{
    return memory_internal;
}

//==============================================================================
inline misc::DataIndexingMode RawDataField::getIndexingMode() const
{
    return indexing_mode;
}

//==============================================================================
inline void RawDataField::setIndexingMode(misc::DataIndexingMode indexing_mode)
{
    this->indexing_mode = indexing_mode;
}

//==============================================================================
inline void RawDataField::throwIfIndexOutOfRange(unsigned long index,
                                                 unsigned long size) const
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
}

bool operator==(const RawDataField& bit_field1, const RawDataField& bit_field2);
bool operator!=(const RawDataField& bit_field1, const RawDataField& bit_field2);

RawDataField operator>>(const RawDataField& bit_field, unsigned int shift_bits);
RawDataField operator<<(const RawDataField& bit_field, unsigned int shift_bits);

#endif
