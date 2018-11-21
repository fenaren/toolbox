#include "Ipv4Header.hpp"
#include "misc.hpp"

//==============================================================================
Ipv4Header::Ipv4Header() :
    version(0)
{
}

//==============================================================================
Ipv4Header::~Ipv4Header()
{
}

//==============================================================================
// Reads the data field from the "buffer" memory location without considering
// byte ordering.  This function is modified from the base class to break out
// the bitfields.
//==============================================================================
unsigned int Ipv4Header::readRaw(const unsigned char* buffer)
{
}

//==============================================================================
// Reads this data packet from the "buffer" memory location.  Each field will be
// byteswapped if its source byte order does not match the byte ordering of the
// host.  This function is modified from the base class to break out the
// bitfields.
//==============================================================================
unsigned int Ipv4Header::readRaw(const unsigned char* buffer,
                                 misc::ByteOrder      source_byte_order)
{
}

//==============================================================================
// Writes the data field to the "buffer" memory location without considering
// byte ordering.  This version is modified from the base class to break out the
// bitfields.
//==============================================================================
unsigned int Ipv4Header::writeRaw(unsigned char* buffer) const
{
}

//==============================================================================
// Writes this data packet to the "buffer" memory location.  Each field will be
// byteswapped if its source byte order does not match the byte ordering of the
// host.  This version is modified from the base class to break out the
// bitfields.
//==============================================================================
unsigned int Ipv4Header::writeRaw(unsigned char*  buffer,
                                  misc::ByteOrder destination_byte_order) const
{
}

//==============================================================================
void Ipv4Header::addDataFields()
{
}
