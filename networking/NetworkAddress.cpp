#include <cstring>
#include <vector>

#include "NetworkAddress.hpp"

//==============================================================================
// Initializes to all zeroes
//==============================================================================
NetworkAddress::NetworkAddress(unsigned short length_bytes)
{
    reserve(length_bytes);
    assign(length_bytes, 0);
}

//==============================================================================
// Initializes to a copy of the data at the given location
//==============================================================================
NetworkAddress::NetworkAddress(const unsigned char* address,
                               unsigned short       length_bytes)
{
    reserve(length_bytes);
    assign(length_bytes, 0); // Must be here to set the size

    readRaw(address);
}

//==============================================================================
// NetworkAddress destructor; does nothing since no dynamic memory is allocated
//==============================================================================
NetworkAddress::~NetworkAddress()
{
}

//==============================================================================
// Assigns a string to a MAC address
//==============================================================================
void NetworkAddress::readRaw(const unsigned char* raw_address)
{
    memcpy(&at(0), raw_address, size());
}

//==============================================================================
// Assigns a string to a MAC address
//==============================================================================
void NetworkAddress::writeRaw(unsigned char* raw_address) const
{
    memcpy(raw_address, &at(0), size());
}
