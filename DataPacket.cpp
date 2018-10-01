#include <string>
#include <vector>

#include "DataField.hpp"
#include "DataPacket.hpp"

//==============================================================================
DataPacket::DataPacket(const std::string& name) :
    DataField(name)
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
        offset += (*i)->readRaw(buffer + offset);
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
        offset += (*i)->writeRaw(buffer + offset);
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
        size_bytes += (*i)->getLengthBytes();
    }

    return size_bytes;
}
