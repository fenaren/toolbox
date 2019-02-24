#if !defined RAW_DATA_FIELD_HPP
#define RAW_DATA_FIELD_HPP

#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <string>

#include "DataField.hpp"

#include "misc.hpp"

class RawDataField : public DataField
{
public:

    // Possible settings for data indexing.  "MS_LEAST" stands for "Most
    // Significant Least" and means the most significant data unit is assigned
    // the least index.  "LS_LEAST" stands for "Least Significant Least" and
    // means the least significant data unit is assigned the least index.  The
    // rest of the indices are assigned in order of increasing or decreasing
    // significance as one would expect.
    enum IndexingMode
    {
        MS_LEAST,
        LS_LEAST
    };

    // Dynamically allocates and maintains data field of size "length".  Units
    // of length are specified in "length_units".  Storage is dynamically
    // allocated.
    // cppcheck-suppress noExplicitConstructor
    RawDataField(unsigned long   length,
                 misc::DataUnits length_units,
                 IndexingMode    bit_indexing_mode = LS_LEAST);

    // Behavior depends on the value of "memory_internal".  If "memory_internal"
    // is true, the data at "buffer" of will be copied into dynamically
    // allocated memory internal to this class.  If "memory_internal" is false,
    // the data at "buffer" will be used by this class in-place and no dynamic
    // memory allocation will occur.
    RawDataField(std::uint8_t*   buffer,
                 unsigned long   length,
                 misc::DataUnits length_units,
                 bool            memory_internal = true,
                 IndexingMode    bit_indexing_mode = LS_LEAST);

    // Copy constructor; dynamically allocates and maintains a bit field that is
    // "length_bytes" in size, and then copies the given bit field into this
    // newly-allocated memory.
    RawDataField(const RawDataField& raw_data_field);

    // Will free the memory at "raw_data" if it is owned by this class
    virtual ~RawDataField();

    // Reads from the "buffer" memory location plus an offset of "bit_offset"
    // bits.  No byteswapping is performed even when "source_byte_order" doesn't
    // match host byte ordering, since this is just raw data.
    virtual unsigned long readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order,
                                  unsigned long   offset_bits = 0);

    // Writes to the "buffer" memory location plus an offset of "bit_offset"
    // bits.  No byteswapping is performed even when "destination_byte_order"
    // doesn't match host byte ordering, since this is just raw data.
    virtual unsigned long writeRaw(std::uint8_t*   buffer,
                                   misc::ByteOrder destination_byte_order,
                                   unsigned long   offset_bits = 0) const;

    // Byte access and mutation, indexed by (obviously)
    std::uint8_t getByte(unsigned int index) const;
    void setByte(unsigned int index, std::uint8_t value);

    // Bit access and mutation.  Affected by the current bit indexing mode (set
    // and get bit indexing mode with setBitIndexingMode() and
    // getBitIndexingMode()).
    bool getBit(unsigned long index) const;
    void setBit(unsigned long index, bool value);

    // Copies a range of bits into the given typed numeric variable.  Useful for
    // pulling things like oddly-sized integers out of raw data.  Affected by
    // the current bit indexing mode (set and get bit indexing mode with
    // setBitIndexingMode() and getBitIndexingMode().  Operation starts by
    // copying bit 0 in the specified range to bit 0 "type_var", and proceeds to
    // higher indices until "count" bits are copied.
    template <class T> void getBitsAsNumericType(
        T&           type_var,
        unsigned int start_bit = 0,
        unsigned int count     = sizeof(T) * BITS_PER_BYTE) const;

    // Copies a range of bits from the given typed numeric variable.  Useful for
    // pushing reduced-width things like oddly-sized integers into raw data.
    // Affected by the current bit indexing mode (set and get bit indexing mode
    // with setBitIndexingMode() and getBitIndexingMode().  Operation starts by
    // copying bit 0 in "type_var" to bit 0 in the specified range, and proceeds
    // to higher indices until "count" bits are copied.
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

    // Simple accessor for memory_internal; modifying this would require
    // functionality that isn't implemented yet, so now "memory_internal" can't
    // be set after construction time.
    bool getMemoryInternal() const;

    // Bit indexing mode accessor.  Bit indexing mode determines how bits within
    // each byte are indexed.  Right now two modes are supported.  One assigns
    // the least significant bit in each byte the least index (LS_LEAST), the
    // other assigns the most significant bit in each byte the least index
    // (MS_LEAST).
    IndexingMode getBitIndexingMode() const;

    // Bit indexing mode mutator.  See getBitIndexingMode() comment for more
    // information.
    void setBitIndexingMode(IndexingMode bit_indexing_mode);

    // Assignment from other RawDataFields; copies all internal state including
    // what's at "raw_data"
    RawDataField& operator=(const RawDataField& raw_data_field);

    // Uses leftShift()
    RawDataField& operator<<=(unsigned int shift_bits);

    // Uses rightShift()
    RawDataField& operator>>=(unsigned int shift_bits);

protected:

    // Tosses a std::out_of_range exception if index >= size
    static void throwIfIndexOutOfRange(unsigned long index, unsigned long size);

private:

    // Only for use as a delegating constructor.  Sets length_bits and indexing
    // mode.
    RawDataField(unsigned long   length,
                 misc::DataUnits length_units,
                 bool            memory_internal,
                 IndexingMode    bit_indexing_mode);

    // Reference to the raw data represented by this class
    std::uint8_t* raw_data;

    // Field is this many bits in length
    unsigned long length_bits;

    // Does this class own the memory at "raw_data"?
    bool memory_internal;

    // How are we indexing individual bits within bytes?  See the comment on
    // IndexingMode for more information.  Has no relevance across bytes.
    IndexingMode bit_indexing_mode;
};

//==============================================================================
inline unsigned long RawDataField::getLengthBits() const
{
    return length_bits;
}

//==============================================================================
inline bool RawDataField::getMemoryInternal() const
{
    return memory_internal;
}

//==============================================================================
inline RawDataField::IndexingMode RawDataField::getBitIndexingMode() const
{
    return bit_indexing_mode;
}

//==============================================================================
inline void RawDataField::setBitIndexingMode(
    RawDataField::IndexingMode bit_indexing_mode)
{
    this->bit_indexing_mode = bit_indexing_mode;
}

//==============================================================================
inline void RawDataField::throwIfIndexOutOfRange(unsigned long index,
                                                 unsigned long size)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
}

bool operator==(const RawDataField& lhs, const RawDataField& rhs);
bool operator!=(const RawDataField& lhs, const RawDataField& rhs);

RawDataField operator>>(const RawDataField& lhs, unsigned int rhs);
RawDataField operator<<(const RawDataField& lhs, unsigned int rhs);

#endif
