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
unsigned int DataField::readRaw(const unsigned char* buffer)
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return readRaw(buffer, byte_order);
}

//==============================================================================
// Writes the data field to the "buffer" memory location without considering
// byte ordering.
//==============================================================================
unsigned int DataField::writeRaw(unsigned char* buffer) const
{
    // Call the virtual method with the host byte ordering.  If the virtual
    // method is implemented like it should be it won't do any byteswapping.
    return writeRaw(buffer, byte_order);
}
