#include <cstdint>
#include <vector>

#include "DataField.hpp"
#include "DataPacket.hpp"

//==============================================================================
DataPacket::DataPacket(unsigned int bit_alignment) :
    DataField()
{
    setBitAlignment(bit_alignment);
}

//==============================================================================
DataPacket::~DataPacket()
{
}

//==============================================================================
// Reads the data field from the "buffer" memory location without considering
// byte ordering.
//==============================================================================
unsigned int DataPacket::readRaw(const std::uint8_t* buffer,
                                 unsigned int        offset_bits)
{
    return DataField::readRaw(buffer, offset_bits);
}

//==============================================================================
// Reads this data packet from the "buffer" memory location.  Each field will be
// byteswapped if its source byte order does not match the byte ordering of the
// host.
//==============================================================================
unsigned int DataPacket::readRaw(const std::uint8_t* buffer,
                                 misc::ByteOrder     source_byte_order,
                                 unsigned int        offset_bits)
{
    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        offset_bits += (*i)->readRaw(
            buffer,
            source_byte_order,
            offset_bits + computePaddingBits((*i)->getLengthBits()));
    }

    return offset_bits;
}

//==============================================================================
// Writes the data field to the "buffer" memory location without considering
// byte ordering.
//==============================================================================
unsigned int DataPacket::writeRaw(std::uint8_t* buffer,
                                  unsigned int  offset_bits) const
{
    return DataField::writeRaw(buffer, offset_bits);
}

//==============================================================================
// Writes this data packet to the "buffer" memory location.  Each field will be
// byteswapped if its source byte order does not match the byte ordering of the
// host.
//==============================================================================
unsigned int DataPacket::writeRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder destination_byte_order,
                                  unsigned int    offset_bits) const
{
    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        offset_bits += (*i)->writeRaw(
            buffer,
            destination_byte_order,
            offset_bits + computePaddingBits((*i)->getLengthBits()));
    }

    return offset_bits;
}

//==============================================================================
// Returns the size of this field in bytes.  This will equal the number of bytes
// written by writeRaw() and read by readRaw().
//==============================================================================
unsigned int DataPacket::getLengthBits() const
{
    unsigned int length_bits = 0;

    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        unsigned int field_length_bits = (*i)->getLengthBits();
        length_bits += field_length_bits + computePaddingBits(field_length_bits);
    }

    return length_bits;
}

//==============================================================================
// Computes amount of padding needed after a field given the current byte
// alignment setting
//==============================================================================
unsigned int DataPacket::computePaddingBits(
    unsigned int offset_bits, unsigned int field_length_bits) const
{
    unsigned int padding_bits = 0;

    unsigned int extra_bits =
        (offset_bits + field_length_bits) % bit_alignment;

    if (extra_bits > 0)
    {
        // extra_bytes must be less than byte_alignment by the definition of
        // modulus so no need to worry about underflow
        padding_bits = bit_alignment - extra_bits;
    }

    return padding_bits;
}
