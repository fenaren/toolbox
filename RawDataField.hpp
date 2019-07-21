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
                 bool            memory_internal   = true,
                 IndexingMode    bit_indexing_mode = LS_LEAST);

    // Const-compatible version of the member function declared immediately
    // above, EXCEPT usage of this constructor puts objects of this class into
    // "const mode", meaning they will not do anything to modify the memory at
    // 'buffer'.  Functions that would modify the buffer are prevented from
    // doing so with exceptions if they cannot be prevented from doing so at
    // compile time.
    RawDataField(const std::uint8_t* buffer,
                 unsigned long       length,
                 misc::DataUnits     length_units,
                 bool                memory_internal   = true,
                 IndexingMode        bit_indexing_mode = LS_LEAST);

    // Copy constructor; dynamically allocates and maintains a bit field that is
    // "length_bytes" in size, and then copies the given bit field into this
    // newly-allocated memory.
    RawDataField(const RawDataField& raw_data_field);

    // Will free the memory at "raw_data" if it is owned by this class
    virtual ~RawDataField();

    // Reads from the "buffer" memory location.  No byteswapping is performed
    // even when "source_byte_order" doesn't match host byte ordering, since
    // this is just raw data.
    virtual unsigned long readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order);

    // Const-compatible version of the above member function
    virtual unsigned long readRaw(const std::uint8_t* buffer,
                                  misc::ByteOrder     source_byte_order);

    // Writes to the "buffer" memory location.  No byteswapping is performed
    // even when "destination_byte_order" doesn't match host byte ordering,
    // since this is just raw data.
    virtual unsigned long writeRaw(
        std::uint8_t*   buffer,
        misc::ByteOrder destination_byte_order) const;

    // Byte access and mutation in array order
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

    // Bits shift toward the greatest index.  Behavior is affected by the
    // current bit indexing mode.
    void shiftUp(unsigned int shift_bits);

    // Bits shift toward the least index.  Behavior is affected by the current
    // bit indexing mode.
    void shiftDown(unsigned int shift_bits);

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

    // Returns true if this class is in "const mode", meaning it was constructed
    // using the const buffer constructor.  In this mode this class won't modify
    // the contents of that buffer.  To protect the data, Const mode can't be
    // changed after construction time.
    bool getConstMode() const;

    // Assignment from other RawDataFields; copies all internal state including
    // what's at "raw_data"
    RawDataField& operator=(const RawDataField& raw_data_field);

protected:

    // Tosses a std::out_of_range exception if index >= size
    static void throwIfIndexOutOfRange(unsigned long index, unsigned long size);

private:

    // Only for use as a delegating constructor.  Sets length_bits and indexing
    // mode.
    RawDataField(std::uint8_t*       buffer,
                 const std::uint8_t* buffer_const,
                 unsigned long       length,
                 misc::DataUnits     length_units,
                 bool                memory_internal,
                 IndexingMode        bit_indexing_mode,
                 bool                const_mode);

    void constModeExceptionCheck() const;

    // Reference to the raw data represented by this class
    std::uint8_t* raw_data;

    // Another reference to the raw data represented by this class, but is used
    // only if the const buffer constructor was used
    const std::uint8_t* raw_data_const;

    // Field is this many bits in length
    unsigned long length_bits;

    // Does this class own the memory at "raw_data"?
    bool memory_internal;

    // How are we indexing individual bits within bytes?  See the comment on
    // IndexingMode for more information.  Has no relevance across bytes.
    IndexingMode bit_indexing_mode;

    // Is true if the const buffer constructor was used to construct objects of
    // this class.
    bool const_mode;
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

//==============================================================================
inline bool RawDataField::getConstMode() const
{
    return const_mode;
}

//==============================================================================
inline void RawDataField::constModeExceptionCheck() const
{
    if (!memory_internal && const_mode)
    {
        throw std::runtime_error("");
    }
}

bool operator==(const RawDataField& lhs, const RawDataField& rhs);
bool operator!=(const RawDataField& lhs, const RawDataField& rhs);

#endif
