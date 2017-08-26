#include "MacAddress.hpp"

#include <cstdio>
#include <cstring>
#include <ostream>

//==============================================================================
// MacAddress constructor; initializes to all zeros
//==============================================================================
MacAddress::MacAddress()
{
    memset(&mac_address, 0, 6);
}

//==============================================================================
// MacAddress copy constructor; copies the address of the given MAC address
//==============================================================================
MacAddress::MacAddress(const MacAddress& mac_address)
{
    *this = mac_address;
}

//==============================================================================
// MacAddress destructor; does nothing since no dynamic memory is allocated
//==============================================================================
MacAddress::~MacAddress()
{
}

//==============================================================================
// Assigns one MAC address to another
//==============================================================================
MacAddress& MacAddress::operator=(const MacAddress& mac_address)
{
    memcpy(&this->mac_address, &mac_address, 6);

    return *this;
}

//==============================================================================
// Compares two MAC addresses for equality
//==============================================================================
bool MacAddress::operator==(const MacAddress& mac_address)
{
    return memcmp(&this->mac_address[0], &mac_address, 6) == 0;
}

//==============================================================================
// Allows the use of brackets to index into the MAC address
//==============================================================================
unsigned char& MacAddress::operator[](const unsigned int byteNum)
{
    return mac_address[byteNum];
}

//==============================================================================
// Writes string representation of self to the ostream
//==============================================================================
std::ostream& operator<<(std::ostream& os, MacAddress& mac_address)
{
    // 18 characters for the whole representation; 12 for the actual numbers, 5
    // for the colons in-between, and 1 on the end for the null
    char mac_cstr[18];
    mac_cstr[17] = 0;
    sprintf(mac_cstr,
            "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_address[0],
            mac_address[1],
            mac_address[2],
            mac_address[3],
            mac_address[4],
            mac_address[5]);

    return os << mac_cstr;
}

std::istream& operator>>(std::istream& is, MacAddress& mac_address)
{
    // Scan the device's MAC address into temporary storage
    /*sscanf(token.c_str(),
           "%2x:%2x:%2x:%2x:%2x:%2x",
           &temp_mac[0],
           &temp_mac[1],
           &temp_mac[2],
           &temp_mac[3],
           &temp_mac[4],
           &temp_mac[5]);*/
    
    return is;
}
