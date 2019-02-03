#if !defined BYTE_FIELD_HPP
#define BYTE_FIELD_HPP

#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <stdexcept>
#include <string>

#include "DataField.hpp"

#include "misc.hpp"

class ByteField : public DataField
{
public:

    // Dynamically allocates and maintains a byte field that is "length_bytes"
    // in size.  All bits are initially unset (set to 0).  Storage is
    // dynamically allocated.
    // cppcheck-suppress noExplicitConstructor
    ByteField(unsigned long length_bytes);

    // Behavior depends on the value of "memory_internal".  If "memory_internal"
    // is true, the data at "buffer" of length "length_bytes" will be copied
    // into dynamically-allocated memory internal to this class.  If
    // "memory_internal" is false, the data at "buffer" of length "length_bytes"
    // will be used by this class in-place and no dynamic memory allocation will
    // occur.
    ByteField(std::uint8_t* buffer,
              unsigned long length_bytes,
              bool          memory_internal = true);

    // Copy constructor; dynamically allocates and maintains a byte field that
    // is "length_bytes" in size, and then copies the given byte field into this
    // newly-allocated memory.
    ByteField(const ByteField& byte_field);

    // Will free the memory at "byte_field_raw" if it is owned by this class
    virtual ~ByteField();

    // Reads a raw byte field from the "buffer" memory location.  Byte ordering
    // has no relevance to byte fields so no byte swapping is performed.
    virtual unsigned long readRaw(std::uint8_t* buffer,
                                  unsigned long offset_bits = 0);

    // Reads a raw byte field from the "buffer" memory location.  This
    // function is required by the framework to be implemented here, despite
    // being functionally identical to the single-argument version defined
    // above.  If byte ordering were relevant to byte fields (in the
    // general sense of the term) this function would be where that difference
    // would be handled.
    virtual unsigned long readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order,
                                  unsigned long   offset_bits = 0);

    // Writes this byte field to the "buffer" memory location.  Byte ordering has
    // no relevance to byte fields so no byte swapping is performed.
    virtual unsigned long writeRaw(std::uint8_t* buffer,
                                   unsigned long offset_bits = 0) const;

    // Writes this byte field to the "buffer" memory location.  This function is
    // required by the framework to be implemented here, despite being
    // functionally identical to the single-argument version defined above.  If
    // byte ordering were relevant to byte fields (in the general sense of the
    // term) this function would be where that difference would be handled.
    virtual unsigned long writeRaw(std::uint8_t*   buffer,
                                   misc::ByteOrder destination_byte_order,
                                   unsigned long   offset_bits = 0) const;

    // Returns the size of this byte field in bytes.  This will equal the number
    // of bytes written by writeRaw() and read by readRaw().
    virtual unsigned long getLengthBytes() const;

    // Simple accessor for memory_internal
    bool getMemoryInternal() const;

    std::uint8_t getByte(unsigned long index) const;
    void setByte(unsigned long index, std::uint8_t byte);

    misc::DataIndexingMode getIndexingMode() const;
    void setIndexingMode(misc::DataIndexingMode indexing_mode);

    ByteField& operator=(const ByteField& byte_field);

private:

    // Tosses a std::out_of_range exception if octet >= length_bytes
    void throwIfIndexOutOfRange(unsigned long index) const;

    // Raw byte field is stored at this location
    std::uint8_t* byte_field_raw;

    // Raw byte field is this many bytes in length
    unsigned long length_bytes;

    // Does this class own the memory at "byte_field_raw"?
    bool memory_internal;

    // Defaults for indexing modes for bits and bytes
    misc::DataIndexingMode indexing_mode;
};

//==============================================================================
inline unsigned long ByteField::getLengthBytes() const
{
    return length_bytes;
}

//==============================================================================
inline misc::DataIndexingMode ByteField::getIndexingMode() const
{
    return indexing_mode;
}

//==============================================================================
inline std::uint8_t ByteField::getByte(unsigned long index) const
{
    throwIfIndexOutOfRange(index);

    unsigned long real_index = index;

    if (indexing_mode == misc::LS_ZERO)
    {
        real_index = length_bytes - index - 1;
    }

    return byte_field_raw[real_index];
}

//==============================================================================
inline void ByteField::setByte(unsigned long index, std::uint8_t byte)
{
    throwIfIndexOutOfRange(index);

    unsigned long real_index = index;

    if (indexing_mode == misc::LS_ZERO)
    {
        real_index = length_bytes - index - 1;
    }

    byte_field_raw[real_index] = byte;
}

//==============================================================================
inline void ByteField::setIndexingMode(misc::DataIndexingMode indexing_mode)
{
    this->indexing_mode = indexing_mode;
}

//==============================================================================
inline bool ByteField::getMemoryInternal() const
{
    return memory_internal;
}

//==============================================================================
inline void ByteField::throwIfIndexOutOfRange(unsigned long index) const
{
    if (index >= length_bytes)
    {
        throw std::out_of_range("Bit index out of range");
    }
}

bool operator==(const ByteField& byte_field1, const ByteField& byte_field2);
bool operator!=(const ByteField& byte_field1, const ByteField& byte_field2);

#endif
