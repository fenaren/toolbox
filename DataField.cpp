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
// Reads the data field from the "buffer" memory location without considering
// byte ordering.
//==============================================================================
unsigned long DataField::readRaw(std::uint8_t* buffer,
                                 unsigned long bit_offset)
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return readRaw(buffer, byte_order, bit_offset);
}

//==============================================================================
// Writes the data field to the "buffer" memory location without considering
// byte ordering.
//==============================================================================
unsigned long DataField::writeRaw(std::uint8_t* buffer,
                                  unsigned long bit_offset) const
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return writeRaw(buffer, byte_order, bit_offset);
}

//==============================================================================
void DataField::normalizeMemoryLocation(std::uint8_t*& buffer,
                                        unsigned long& offset_bits) const
{
    std::ldiv_t div_result = std::ldiv(offset_bits, BITS_PER_BYTE);

    // Take all the bytes out of offset_bits
    buffer += div_result.quot;
    offset_bits = div_result.rem;
}
