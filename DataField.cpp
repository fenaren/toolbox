#include <cstdlib>

#include "DataField.hpp"

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
    return readRaw(buffer, getByteOrder(), 0);
}

//==============================================================================
unsigned long DataField::readRaw(std::uint8_t*   buffer,
                                 misc::ByteOrder byte_order)
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return readRaw(buffer, byte_order, 0);
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
    return writeRaw(buffer, getByteOrder(), 0);
}

//==============================================================================
unsigned long DataField::writeRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder byte_order) const
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return writeRaw(buffer, byte_order, 0);
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
