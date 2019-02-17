#include <cmath>
#include <cstdint>
#include <vector>

#include "DataField.hpp"
#include "DataPacket.hpp"
#include "misc.hpp"

//==============================================================================
DataPacket::DataPacket(unsigned int    alignment,
                       misc::DataUnits alignment_units) :
    DataField()
{
    setAlignment(alignment, alignment_units);
}

//==============================================================================
DataPacket::~DataPacket()
{
}

//==============================================================================
unsigned long DataPacket::readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order,
                                  unsigned long   offset_bits)
{
    unsigned long bits_read = 0;

    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        // This will take all the bytes out of offset_bits and bump buffer
        // accordingly.  As a result offset_bits will be < BITS_PER_BYTE.
        normalizeMemoryLocation(buffer, offset_bits);

        unsigned long offset_bits_initial = offset_bits;

        // Tell the current field to read and record the number of bits it read
        offset_bits += (*i)->readRaw(buffer, source_byte_order, offset_bits);

        // Bump the offset to the next alignment point
        offset_bits = misc::smallestMultipleOfXGreaterOrEqualToY(alignment_bits,
                                                                 offset_bits);

        // This field plus the padding after it
        bits_read += offset_bits - offset_bits_initial;
    }

    return bits_read;
}

//==============================================================================
unsigned long DataPacket::writeRaw(std::uint8_t*   buffer,
                                   misc::ByteOrder destination_byte_order,
                                   unsigned long   offset_bits) const
{
    unsigned long bits_written = 0;

    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        // This will take all the bytes out of offset_bits and bump buffer
        // accordingly.  As a result offset_bits will be < BITS_PER_BYTE.
        normalizeMemoryLocation(buffer, offset_bits);

        unsigned long offset_bits_initial = offset_bits;

        // Tell the current field to read and record the number of bits it read
        offset_bits +=
            (*i)->writeRaw(buffer, destination_byte_order, offset_bits);

        // Bump the offset to the next alignment point
        offset_bits = misc::smallestMultipleOfXGreaterOrEqualToY(alignment_bits,
                                                                 offset_bits);

        // This field plus the padding after it
        bits_written += offset_bits - offset_bits_initial;
    }

    // The number of bits we actually wrote
    return bits_written;
}

//==============================================================================
unsigned long DataPacket::getLengthBits() const
{
    unsigned long length_bits = 0;

    for (std::vector<DataField*>::const_iterator i = data_fields.begin();
         i != data_fields.end();
         ++i)
    {
        // Increase packet length by the length of the current packet
        length_bits += (*i)->getLengthBits();

        // Increase packet length again to account for alignment
        length_bits = misc::smallestMultipleOfXGreaterOrEqualToY(alignment_bits,
                                                                 length_bits);
    }

    return length_bits;
}
