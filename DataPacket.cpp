#include <cmath>
#include <cstdint>
#include <vector>

#include "DataField.hpp"
#include "DataPacket.hpp"
#include "misc.hpp"

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
unsigned long DataPacket::readRaw(std::uint8_t* buffer,
                                 unsigned int   offset_bits)
{
    return DataField::readRaw(buffer, offset_bits);
}

//==============================================================================
// Reads this data packet from the "buffer" memory location.  Each field will be
// byteswapped if its source byte order does not match the byte ordering of the
// host.
//==============================================================================
unsigned long DataPacket::readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order,
                                  unsigned int    offset_bits)
{
    unsigned long bits_read = 0;

    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        // This will take all the bytes out of offset_bits and bump buffer
        // accordingly.  As a result offset_bits will be < BITS_PER_BYTE.
        normalizeBufferAndOffsetBits(buffer, offset_bits);

        // Tell the current field to read and record the number of bits it read
        unsigned long field_width_bits =
            (*i)->readRaw(buffer, source_byte_order, offset_bits);

        // Add the number of bits we just read to the running total
        bits_read += field_width_bits;

        // Bump the offset by the length of the field we just read
        offset_bits += field_width_bits;

        // Bump the offset to the next alignment point
        offset_bits = misc::smallestMultipleOfXGreaterOrEqualToY(alignment_bits,
                                                                 offset_bits);
    }

    return bits_read;
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
    // We did not write these bits so they come out at the end
    unsigned int offset_bits_initial = offset_bits;

    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        // Bump the offset past the field we just read
        offset_bits +=
            (*i)->writeRaw(buffer, destination_byte_order, offset_bits);

        // Bump the offset to the next alignment point
        offset_bits = misc::smallestMultipleOfXGreaterOrEqualToY(alignment_bits,
                                                                 offset_bits);
    }

    // The number of bits we actually wrote
    return offset_bits - offset_bits_initial;
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
    std::div_t div_result = std::div(offset_bits, BITS_PER_BYTE);

    // Take all the bytes out of offset_bits
    buffer += div_result.quot;
    offset_bits = div_result.rem;
}
