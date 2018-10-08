#include <vector>

#include "DataField.hpp"
#include "DataPacket.hpp"

//==============================================================================
DataPacket::DataPacket(unsigned int byte_alignment) :
    DataField()
{
    setByteAlignment(byte_alignment);
}

//==============================================================================
DataPacket::~DataPacket()
{
}

//==============================================================================
// Reads the data field from the "buffer" memory location without considering
// byte ordering.
//==============================================================================
unsigned int DataPacket::readRaw(const unsigned char* buffer)
{
    return DataField::readRaw(buffer);
}

//==============================================================================
// Reads this data packet from the "buffer" memory location.  Each field will be
// byteswapped if its source byte order does not match the byte ordering of the
// host.
//==============================================================================
unsigned int DataPacket::readRaw(const unsigned char* buffer,
                                 misc::ByteOrder      source_byte_order)
{
    unsigned int offset = 0;

    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        unsigned int field_length = (*i)->readRaw(buffer + offset,
                                                  source_byte_order);
        offset += field_length + computePadding(field_length);
    }

    return offset;
}

//==============================================================================
// Writes the data field to the "buffer" memory location without considering
// byte ordering.
//==============================================================================
unsigned int DataPacket::writeRaw(unsigned char* buffer) const
{
    return DataField::writeRaw(buffer);
}

//==============================================================================
// Writes this data packet to the "buffer" memory location.  Each field will be
// byteswapped if its source byte order does not match the byte ordering of the
// host.
//==============================================================================
unsigned int DataPacket::writeRaw(unsigned char*  buffer,
                                  misc::ByteOrder destination_byte_order) const
{
    unsigned int offset = 0;

    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        unsigned int field_length = (*i)->writeRaw(buffer + offset,
                                                   destination_byte_order);
        offset += field_length + computePadding(field_length);
    }

    return offset;
}

//==============================================================================
// Returns the size of this field in bytes.  This will equal the number of bytes
// written by writeRaw() and read by readRaw().
//==============================================================================
unsigned int DataPacket::getLengthBytes() const
{
    unsigned int offset = 0;

    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        unsigned int field_length = (*i)->getLengthBytes();
        offset += field_length + computePadding(field_length);
    }

    return offset;
}

//==============================================================================
// Computes amount of padding needed after a field given the current byte
// alignment setting
//==============================================================================
unsigned int DataPacket::computePadding(unsigned int field_length) const
{
    unsigned int extra_bytes = field_length % byte_alignment;
    unsigned int padding     = 0;

    if (extra_bytes > 0)
    {
        // extra_bytes must be less than byte_alignment by the definition of
        // modulus so no need to worry about underflow
        padding = byte_alignment - extra_bytes;
    }

    return padding;
}
