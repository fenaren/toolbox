#include <cmath>
#include <cstdlib>

#include "DataField.hpp"

#include "RawDataField.hpp"
#include "misc.hpp"

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
unsigned long DataField::readRaw(std::uint8_t* buffer)
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return readRaw(buffer, getByteOrder());
}

//==============================================================================
unsigned long DataField::readRaw(std::uint8_t*   buffer,
                                 misc::ByteOrder source_byte_order,
                                 unsigned long   bit_offset)
{
    normalizeMemoryLocation(buffer, bit_offset);

    // Handle the simple no-offset case without going to all the trouble of the
    // offset case
    if (bit_offset == 0)
    {
        return readRaw(buffer, source_byte_order);
    }

    // This field is offset.  To handle this in a generic way at this level,
    // we'll use the given buffer to shift the data by offset_bits so there's no
    // longer any offset.  Then we'll do the read like normal.  Afterwards we'll
    // shift the data back to where it was and put the first byte back in
    // place.  This should leave things exactly the way we left them.

    // All the other alternatives involve using memory we don't have.  This
    // would mean dynamically allocating memory here or statitcally allocating
    // enough data store this packet in case this happens, which would be
    // probably be wasteful in general.  Offset packets are expected to be
    // uncommon.

    // Save the first byte to put back later
    std::uint8_t first_byte = buffer[0];

    // Use a RawDataField to shift the whole packet down so there's no offset
    RawDataField buffer_rdf(
        buffer, getLengthBits() + bit_offset, misc::BITS, false);
    buffer_rdf >>= bit_offset;

    // Data is no longer offset so a normal read will work
    unsigned long bits_read = readRaw(buffer, source_byte_order);

    // Mask the bits we shouldn't have touched back into the first byte
    std::uint8_t mask = std::pow(2, bit_offset) - 1;
    first_byte &= mask;
    buffer[0] &= ~mask;
    buffer[0] |= first_byte;

    return bits_read;
}

//==============================================================================
unsigned long DataField::readRaw(std::uint8_t* buffer,
                                 unsigned long bit_offset)
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return readRaw(buffer, getByteOrder(), bit_offset);
}

//==============================================================================
unsigned long DataField::writeRaw(std::uint8_t* buffer) const
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return writeRaw(buffer, getByteOrder());
}

//==============================================================================
unsigned long DataField::writeRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder destination_byte_order,
                                  unsigned long   bit_offset) const
{
    normalizeMemoryLocation(buffer, bit_offset);

    // Handle the simple no-offset case without going to all the trouble of the
    // offset case
    if (bit_offset == 0)
    {
        return writeRaw(buffer, destination_byte_order);
    }

    // This field is offset.  To handle this in a generic way at this level,
    // we'll write into the buffer as if the field weren't offset, then shift
    // the data into its correct offset location.  This will briefly destroy
    // data in the buffer but we'll save that data and put it back where it
    // should be as the last thing we do.

    // All the other alternatives involve using memory we don't have.  This
    // would mean dynamically allocating memory here or statitcally allocating
    // enough data store this packet in case this happens, which would be
    // probably be wasteful in general.  Offset packets are expected to be
    // uncommon.

    // Save the first byte, we have to mask this back in later
    std::uint8_t first_byte = buffer[0];

    // Do the write like normal.  This destroys data in the first byte but it's
    // okay, we've saved that.
    unsigned long bits_written = writeRaw(buffer, destination_byte_order);

    // Shift the field into the correct offset location
    RawDataField buffer_rdf(
        buffer, getLengthBits() + bit_offset, misc::BITS, false);
    buffer_rdf <<= bit_offset;

    // Mask the bits we shouldn't have touched back into the first byte
    std::uint8_t mask = std::pow(2, bit_offset) - 1;
    first_byte &= mask;
    buffer[0] &= ~mask;
    buffer[0] |= first_byte;

    return bits_written;
}

//==============================================================================
unsigned long DataField::writeRaw(std::uint8_t* buffer,
                                  unsigned long bit_offset) const
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return writeRaw(buffer, getByteOrder(), bit_offset);
}

//==============================================================================
void DataField::normalizeMemoryLocation(std::uint8_t*& buffer,
                                        unsigned long& offset_bits)
{
    std::ldiv_t div_result = std::ldiv(offset_bits, BITS_PER_BYTE);

    // Take all the bytes out of offset_bits
    buffer += div_result.quot;
    offset_bits = div_result.rem;
}
