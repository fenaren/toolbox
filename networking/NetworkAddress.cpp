#include <cstring>
#include <vector>

#include "NetworkAddress.hpp"

//==============================================================================
// NetworkAddress constructor; initializes to all zeros
//==============================================================================
NetworkAddress::NetworkAddress(unsigned short length_bytes)
{
    reserve(length_bytes);
    assign(length_bytes, 0);
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
void NetworkAddress::readRaw(const char* buf)
{
    memcpy(&at(0), buf, size());
}

//==============================================================================
// Assigns a string to a MAC address
//==============================================================================
void NetworkAddress::writeRaw(char* buf) const
{
    memcpy(buf, &at(0), size());
}
