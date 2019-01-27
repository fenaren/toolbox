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
unsigned long DataPacket::readRaw(std::uint8_t* buffer)
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return DataField::readRaw(buffer);
}

//==============================================================================
unsigned long DataPacket::readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder byte_order)
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return DataField::readRaw(buffer, byte_order);
}

//==============================================================================
unsigned long DataPacket::readRaw(std::uint8_t* buffer,
                                  unsigned long bit_offset)
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return DataField::readRaw(buffer, bit_offset);
}

//==============================================================================
// Reads this data packet from the "buffer" memory location.  Each field will be
// byteswapped if its source byte order does not match the byte ordering of the
// host.
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
unsigned long DataPacket::writeRaw(std::uint8_t* buffer) const
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return DataField::writeRaw(buffer);
}

//==============================================================================
unsigned long DataPacket::writeRaw(std::uint8_t*   buffer,
                                   misc::ByteOrder byte_order) const
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return DataField::writeRaw(buffer, byte_order);
}

//==============================================================================
unsigned long DataPacket::writeRaw(std::uint8_t* buffer,
                                   unsigned long bit_offset) const
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return DataField::writeRaw(buffer, bit_offset);
}

//==============================================================================
// Writes this data packet to the "buffer" memory location.  Each field will be
// byteswapped if its source byte order does not match the byte ordering of the
// host.
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
        length_bits += (*i)->getLengthBits();
        length_bits = misc::smallestMultipleOfXGreaterOrEqualToY(alignment_bits,
                                                                 length_bits);
    }

    return length_bits;
}
