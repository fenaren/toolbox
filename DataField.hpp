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

    friend class DataField_test;

    // Neither of these do anything
    DataField();
    virtual ~DataField();

    // Reads this field from memory.  "source_byte_order" specifies the byte
    // ordering of the field as it rests in memory, and if that ordering doesn't
    // match host ordering then it's byteswapped before being interpreted.  All
    // three of the overloaded readRaw() member functions defined below use this
    // function.
    virtual unsigned long readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order) = 0;

    // Const-compatible version of the above member function
    virtual unsigned long readRaw(const std::uint8_t* buffer,
                                  misc::ByteOrder     source_byte_order) = 0;

    // Same as the two-argument virtual readRaw() declared above but with byte
    // swapping disabled.
    unsigned long readRaw(std::uint8_t* buffer);

    // Const-compatible version of the above member function
    unsigned long readRaw(const std::uint8_t* buffer);

    // Same as the virtual readRaw() declared above, but this readRaw() supports
    // reading from a bit offset from the beginning of the buffer.  Intended to
    // be used to read fields which do not begin on a byte boundary.  IMPORTANT
    // NOTE: Buffer content will be modified and then returned to its original
    // state at the end of the operation.
    unsigned long readRaw(std::uint8_t*   buffer,
                          misc::ByteOrder source_byte_order,
                          unsigned long   bit_offset);

    // Const-compatible version of the above member function
    unsigned long readRaw(const std::uint8_t* buffer,
                          misc::ByteOrder     source_byte_order,
                          unsigned long       bit_offset);

    // Same as the three-argument readRaw() declared above but with byte
    // swapping disabled.
    unsigned long readRaw(std::uint8_t* buffer, unsigned long bit_offset);

    // Const-compatible version of the above member function
    unsigned long readRaw(const std::uint8_t* buffer, unsigned long bit_offset);

    // Writes this field to memory.  "destination_byte_order" specifies the byte
    // ordering of the field as it should rest in memory.  Field data will be
    // byteswapped into memory if memory order doesn't match host order.
    virtual unsigned long writeRaw(
        std::uint8_t*   buffer,
        misc::ByteOrder destination_byte_order) const = 0;

    // Same as the virtual writeRaw() declared immediately above but with
    // byteswapping disabled.
    unsigned long writeRaw(std::uint8_t* buffer) const;

    // Same as the virtual writeRaw() declared above, but this writeRaw()
    // supports writing to a bit offset from the beginning of the buffer.
    // Intended to be used to write fields which do not begin on a byte
    // boundary.  IMPORTANT NOTE: Buffer content will be modified and then
    // returned to its original state at the end of the operation.
    unsigned long writeRaw(std::uint8_t*   buffer,
                           misc::ByteOrder destination_byte_order,
                           unsigned long   bit_offset) const;

    // Same as the writeRaw() defined immediately above but with byteswapping
    // disabled.
    unsigned long writeRaw(std::uint8_t* buffer,
                           unsigned long bit_offset) const;

    // Returns the size of this data field in bits.  This will equal the number
    // of bits written by writeRaw() and read by readRaw().
    virtual unsigned long getLengthBits() const = 0;

    // Returns the length of this field in bytes.  The actual length of this
    // field isn't an integer number of bytes then the returned length is
    // rounded up to the nearest integer multiple.
    unsigned int getLengthBytes() const;

protected:

    // Derived classes can use this to access the static const byte ordering
    // determination stored as a private data member
    static misc::ByteOrder getByteOrder();

    // Takes all the bytes out of "offset_bits" and adds them to buffer.
    // "offset_bits" is reduced to the remainder of offset_bits divided by
    // BITS_PER_BYTE.
    static void normalizeMemoryLocation(std::uint8_t*& buffer,
                                        unsigned long& offset_bits);

    // Const-compatible version of the above member function
    static const std::uint8_t* normalizeMemoryLocation(
        const std::uint8_t* buffer,
        unsigned long&      offset_bits);

private:

    // Stores host ordering for reference by all data fields
    static const misc::ByteOrder byte_order;

    // A meaningful deep copy can't be done here so disallow that and operator=
    DataField(const DataField&);
    //DataField& operator=(const DataField&);
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
