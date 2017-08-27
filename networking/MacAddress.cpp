#include "MacAddress.hpp"

#include <cstdio>
#include <cstring>
#include <ios>
#include <ostream>
#include <sstream>
#include <string>

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
// MacAddress constructor; initializes to match the given string
//==============================================================================
MacAddress::MacAddress(const std::string& mac_address_str)
{
    std::istringstream tempstream(mac_address_str);
    tempstream >> *this;
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
// Compares two MAC addresses for inequality
//==============================================================================
bool MacAddress::operator!=(const MacAddress& mac_address)
{
    // Reuse code by using the == operator
    return !(*this == mac_address);
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
    if (sprintf(mac_cstr,
                "%02x:%02x:%02x:%02x:%02x:%02x",
                mac_address[0],
                mac_address[1],
                mac_address[2],
                mac_address[3],
                mac_address[4],
                mac_address[5]) < 0)
    {
        // Something bad happened, so set the fail bit on the stream
        os.setstate(std::ios_base::failbit);
    }

    return os << mac_cstr;
}

//==============================================================================
// Reads string representation of self from the istream
//==============================================================================
std::istream& operator>>(std::istream& is, MacAddress& mac_address)
{
    // Grab 17 characters from the stream and store temporarily; we use the
    // number 18 below because the istream get function reads the argument - 1
    char tempstr[18];
    is.get(tempstr, 18);

    int tempmac[6];
    // Scan the temporary string as a MAC address
    if (sscanf(tempstr,
               "%2x:%2x:%2x:%2x:%2x:%2x",
               &tempmac[0],
               &tempmac[1],
               &tempmac[2],
               &tempmac[3],
               &tempmac[4],
               &tempmac[5]) != 6)
    {
        // We didn't convert all 6 bytes.  Leave our internal state as-is but
        // set the fail bit on the stream so the user has some way of knowing
        is.setstate(std::ios_base::failbit);
        return is;
    }

    // Copy from temporary storage into permanent storage
    for (unsigned int i = 0; i < 6; i++)
    {
        mac_address[i] = static_cast<unsigned char>(tempmac[i]);
    }

    // I feel like there may be a better way to implement this ...

    return is;
}
