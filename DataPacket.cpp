#include <cmath>
#include <cstdint>
#include <vector>

#include "DataField.hpp"
#include "DataPacket.hpp"

//==============================================================================
DataPacket::DataPacket(unsigned int   alignment,
                       AlignmentUnits alignment_units) :
    DataField()
{
    setAlignment(alignment, alignment_units);
}

//==============================================================================
DataPacket::~DataPacket()
{
}

//==============================================================================
// Reads the data field from the "buffer" memory location without considering
// byte ordering.
//==============================================================================
unsigned long DataPacket::readRaw(const std::uint8_t* buffer,
                                 unsigned int        offset_bits)
{
    return DataField::readRaw(buffer, offset_bits);
}

//==============================================================================
// Reads this data packet from the "buffer" memory location.  Each field will be
// byteswapped if its source byte order does not match the byte ordering of the
// host.
//==============================================================================
unsigned long DataPacket::readRaw(const std::uint8_t* buffer,
                                  misc::ByteOrder     source_byte_order,
                                  unsigned int        offset_bits)
{
    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
//        offset_bits += (*i)->readRaw(buffer, source_byte_order, offset_bits) +
//            computePaddingBits();
    }

    return offset_bits;
}

//==============================================================================
// Writes the data field to the "buffer" memory location without considering
// byte ordering.
//==============================================================================
unsigned long DataPacket::writeRaw(std::uint8_t* buffer,
                                   unsigned int  offset_bits) const
{
    return DataField::writeRaw(buffer, offset_bits);
}

//==============================================================================
// Writes this data packet to the "buffer" memory location.  Each field will be
// byteswapped if its source byte order does not match the byte ordering of the
// host.
//==============================================================================
unsigned long DataPacket::writeRaw(std::uint8_t*   buffer,
                                   misc::ByteOrder destination_byte_order,
                                   unsigned int    offset_bits) const
{
    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
/*        offset_bits += (*i)->writeRaw(
            buffer,
            destination_byte_order,
            offset_bits + computePaddingBits((*i)->getLengthBits()));*/
    }

//    return offset_bits;
    return 0;
}

//==============================================================================
// Returns the size of this field in bytes.  This will equal the number of bytes
// written by writeRaw() and read by readRaw().
//==============================================================================
unsigned long DataPacket::getLengthBits() const
{
    unsigned long length_bits = 0;

    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        unsigned long field_length_bits = (*i)->getLengthBits();
        //length_bits += field_length_bits + computePaddingBits(field_length_bits);
    }

    return length_bits;
}

//==============================================================================
void DataPacket::normalizeBufferAndOffsetBits(std::uint8_t*& buffer,
                                              unsigned int&  offset_bits) const
{
    // Take all the bytes out of offset_bits
    buffer += offset_bits / BITS_PER_BYTE;

    // Keep whatever bits are left
    //offset_bits = computePaddingBits(offset_bits);
}
