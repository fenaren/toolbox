#if !defined DATA_FIELD_HPP
#define DATA_FIELD_HPP

#include "misc.hpp"

class DataField
{
public:

    // Neither of these do anything
    DataField();
    virtual ~DataField();

    // Reads the data field from the "buffer" memory location without
    // considering byte ordering.
    virtual unsigned int readRaw(const unsigned char* buffer);

    // Reads the data field from the "buffer" memory location, swapping if the
    // source byte order does not match the byte ordering of this field
    virtual unsigned int readRaw(const unsigned char* buffer,
                                 misc::ByteOrder      source_byte_order) = 0;

    // Writes the data field to the "buffer" memory location without considering
    // byte ordering.
    virtual unsigned int writeRaw(unsigned char* buffer) const;

    // Writes the data field to the "buffer" memory location, swapping at the
    // destination if the destination byte order does not match the byte
    // ordering of this field
    virtual unsigned int writeRaw(
        unsigned char*  buffer,
        misc::ByteOrder destination_byte_order) const = 0;

    // Returns the size of this data field in bytes.  This will equal the number
    // of bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBytes() const = 0;

protected:

    // Derived classes can use this to access the static const byte ordering
    // determination stored as a private data member
    static misc::ByteOrder getByteOrder();

private:

    // Used by the two argument versions of readRaw() and writeRaw() to
    // determine if byteswapping is needed
    static const misc::ByteOrder byte_order;

    // A meaningful deep copy can't be done here so disallow
    DataField(const DataField&);
    DataField& operator=(const DataField& data_field);
};

inline misc::ByteOrder DataField::getByteOrder()
{
    return byte_order;
}

#endif
