#include <string>
#include <vector>

#include "DataField.hpp"
#include "DataPacket.hpp"

//==============================================================================
DataPacket::DataPacket(const std::string& name) :
    DataField(name),
    byte_alignment(1)
{
}

//==============================================================================
DataPacket::~DataPacket()
{
}

//==============================================================================
// Reads the field from the "buffer" memory location.
//==============================================================================
unsigned int DataPacket::readRaw(const unsigned char* buffer)
{
    unsigned int offset = 0;

    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        unsigned int field_length = (*i)->readRaw(buffer + offset);
        offset += field_length + (field_length % byte_alignment);
    }

    return offset;
}

//==============================================================================
// Writes the field to the "buffer" memory location.
//==============================================================================
unsigned int DataPacket::writeRaw(unsigned char* buffer) const
{
    unsigned int offset = 0;

    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        unsigned int field_length = (*i)->writeRaw(buffer + offset);
        offset += field_length + (field_length % byte_alignment);
    }

    return offset;
}

//==============================================================================
// Returns the size of this field in bytes.  This will equal the number of bytes
// written by writeRaw() and read by readRaw().
//==============================================================================
unsigned int DataPacket::getLengthBytes() const
{
    unsigned int size_bytes = 0;

    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        unsigned int field_length = (*i)->getLengthBytes();
        size_bytes += field_length + (field_length % byte_alignment);
    }

    return size_bytes;
}
