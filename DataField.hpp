#if !defined DATA_FIELD_HPP
#define DATA_FIELD_HPP

#include <cstdint>
#include <cmath>

#include "misc.hpp"

class DataField
{
public:

    // Neither of these do anything
    DataField();
    virtual ~DataField();

    // Reads the data field from the "buffer" memory location without
    // considering byte ordering.
    virtual unsigned long readRaw(std::uint8_t* buffer,
                                  unsigned long bit_offset = 0);

    // Reads the data field from the "buffer" memory location, swapping if the
    // source byte order does not match the byte ordering of this field
    virtual unsigned long readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order,
                                  unsigned long   bit_offset = 0) = 0;

    // Writes the data field to the "buffer" memory location without considering
    // byte ordering.
    virtual unsigned long writeRaw(std::uint8_t* buffer,
                                   unsigned long bit_offset = 0) const;

    // Writes the data field to the "buffer" memory location, swapping at the
    // destination if the destination byte order does not match the byte
    // ordering of this field
    virtual unsigned long writeRaw(
        std::uint8_t*   buffer,
        misc::ByteOrder destination_byte_order,
        unsigned long   bit_offset = 0) const = 0;

    // Returns the size of this data field in bits.  This will equal the number
    // of bits written by writeRaw() and read by readRaw().
    virtual unsigned long getLengthBits() const = 0;

    // Helper function for things that work in integer multiples of bytes.  If
    // the actual length of this field isn't an integer number of bytes then the
    // returned length is rounded up to the nearest integer multiple.
    unsigned int getLengthBytes() const;

protected:

    // Derived classes can use this to access the static const byte ordering
    // determination stored as a private data member
    static misc::ByteOrder getByteOrder();

protected:

    void normalizeMemoryLocation(std::uint8_t*& buffer,
                                 unsigned long& offset_bits) const;

private:

    // Used by the two argument versions of readRaw() and writeRaw() to
    // determine if byteswapping is needed
    static const misc::ByteOrder byte_order;

    // A meaningful deep copy can't be done here so disallow that and operator=
    DataField(const DataField&);
    DataField& operator=(const DataField&);
};

inline unsigned int DataField::getLengthBytes() const
{
    return std::ceil(static_cast<double>(getLengthBits()) /
                     static_cast<double>(BITS_PER_BYTE));
}

inline misc::ByteOrder DataField::getByteOrder()
{
    return byte_order;
}

#endif
