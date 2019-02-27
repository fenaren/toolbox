#if !defined DATA_FIELD_HPP
#define DATA_FIELD_HPP

#include <cmath>
#include <cstdint>

#include "misc.hpp"

// Represents data that can be written and read from memory.  Member functions
// for reading from and writing to memory are declared, but since we don't know
// anything about the data we're representing at this level (don't even know how
// much there is) meaningful content is left to be defined by derived classes.
class DataField
{
public:

    // Neither of these do anything
    DataField();
    virtual ~DataField();

    // The following four methods are all related.  Methods 2-4 are short-hand
    // ways of calling the first method with sensical defaults used in place of
    // the missing arguments.  The first method defines the meaningful content.

    // Reads the data field from the "buffer" memory location plus an offset of
    // "bit_offset" bits, swapping if the source byte order does not match the
    // byte ordering of this field
    unsigned long readRaw(std::uint8_t*   buffer,
                          misc::ByteOrder source_byte_order,
                          unsigned long   bit_offset);

    // Same as the full definition above with source_byte_order = getByteOrder()
    // (this means no swapping) and bit_offset = 0
    unsigned long readRaw(std::uint8_t* buffer);

    // Same as the full definition above with bit_offset = 0
    virtual unsigned long readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order) = 0;

    // Same as the full definition above with source_byte_order = getByteOrder()
    // (this means no swapping)
    unsigned long readRaw(std::uint8_t* buffer,
                          unsigned long bit_offset);

    // The following four methods are all related.  Methods 2-4 are short-hand
    // ways of calling the first method with sensical defaults used in place of
    // the missing arguments.  The first method defines the meaningful content.

    // Writes the data field to the "buffer" memory location plus an offset of
    // "bit_offset" bits, swapping at the destination if the destination byte
    // order does not match the byte ordering of this field
    unsigned long writeRaw(std::uint8_t*   buffer,
                           misc::ByteOrder destination_byte_order,
                           unsigned long   bit_offset) const;

    // Same as the full definition above with destination_byte_order =
    // getByteOrder() (this means no swapping) and bit_offset = 0
    unsigned long writeRaw(std::uint8_t* buffer) const;

    // Same as the full definition above with bit_offset = 0
    virtual unsigned long writeRaw(
        std::uint8_t*   buffer,
        misc::ByteOrder destination_byte_order) const = 0;

    // Same as the full definition above with source_byte_order = getByteOrder()
    // (this means no swapping)
    unsigned long writeRaw(std::uint8_t* buffer,
                           unsigned long bit_offset) const;

    // Returns the size of this data field in bits.  This will equal the number
    // of bits written by writeRaw() and read by readRaw().
    virtual unsigned long getLengthBits() const = 0;

    // Returns the length of this field in bytes.The actual length of this field
    // isn't an integer number of bytes then the returned length is rounded up
    // to the nearest integer multiple.
    unsigned int getLengthBytes() const;

protected:

    // Derived classes can use this to access the static const byte ordering
    // determination stored as a private data member
    static misc::ByteOrder getByteOrder();

protected:

    // Takes all the bytes out of "offset_bits" and adds them to buffer.  Said
    // another way this keeps taking BITS_PER_BYTE out of "offset_bits" and
    // adding 1 to buffer until "offset_bits" is less than 8.
    static void normalizeMemoryLocation(std::uint8_t*& buffer,
                                        unsigned long& offset_bits);

private:

    // Used by the two argument versions of readRaw() and writeRaw() to
    // determine if byteswapping is needed
    static const misc::ByteOrder byte_order;

    // A meaningful deep copy can't be done here so disallow that and operator=
    DataField(const DataField&);
    DataField& operator=(const DataField&);
};

//==============================================================================
inline unsigned int DataField::getLengthBytes() const
{
    return std::ceil(static_cast<double>(getLengthBits()) /
                     static_cast<double>(BITS_PER_BYTE));
}

//==============================================================================
inline misc::ByteOrder DataField::getByteOrder()
{
    return byte_order;
}

#endif
