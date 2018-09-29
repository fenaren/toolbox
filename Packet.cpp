#include <string>
#include <vector>

#include "Field.hpp"
#include "Packet.hpp"

//==============================================================================
Packet::Packet(const std::string& name) :
    Field(name)
{
}

//==============================================================================
Packet::~Packet()
{
}

//==============================================================================
// Reads the field from the "buffer" memory location.
//==============================================================================
unsigned int Packet::readRaw(const unsigned char* buffer)
{
    unsigned int offset = 0;

    for (std::vector<Field*>::const_iterator i = fields.begin();
         i != fields.end();
         ++i)
    {
        offset += (*i)->readRaw(buffer + offset);
    }

    return offset;
}

//==============================================================================
// Writes the field to the "buffer" memory location.
//==============================================================================
unsigned int Packet::writeRaw(unsigned char* buffer) const
{
    unsigned int offset = 0;

    for (std::vector<Field*>::const_iterator i = fields.begin();
         i != fields.end();
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
unsigned int Packet::getSizeBytes() const
{
    unsigned int size_bytes = 0;

    for (std::vector<Field*>::const_iterator i = fields.begin();
         i != fields.end();
         ++i)
    {
        size_bytes += (*i)->getSizeBytes();
    }

    return size_bytes;
}
