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
unsigned long DataField::readRaw(const std::uint8_t* buffer,
                                 unsigned int        bit_offset)
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
                                  unsigned int  bit_offset) const
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return writeRaw(buffer, byte_order, bit_offset);
}
