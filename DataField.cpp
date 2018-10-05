#include "DataField.hpp"

#include "misc.hpp"
#include "miscNetworking.hpp"

// All fields will share the byte order setting retrieved here
const misc::ByteOrder DataField::byte_order = misc::getByteOrder();

//==============================================================================
DataField::DataField()
{
}

//==============================================================================
DataField::~DataField()
{
}

//==============================================================================
// Reads the data field from the "buffer" memory location, swapping it
// internally if the source byte order does not match the byte ordering of this
// field
//==============================================================================
unsigned int DataField::readRaw(const unsigned char* buffer,
                                misc::ByteOrder      source_byte_order)
{
    unsigned int bytes_read = readRaw(buffer);

    if (source_byte_order != byte_order)
    {
        byteswap();
    }

    return bytes_read;
}

//==============================================================================
// Writes the data field to the "buffer" memory location, swapping at the
// destination if the destination byte order does not match the byte ordering of
// this field
//==============================================================================
unsigned int DataField::writeRaw(unsigned char*  buffer,
                                 misc::ByteOrder destination_byte_order) const
{
    unsigned int bytes_written = writeRaw(buffer);

    if (destination_byte_order != byte_order)
    {
        miscNetworking::byteswap(buffer, bytes_written);
    }

    return bytes_written;
}
