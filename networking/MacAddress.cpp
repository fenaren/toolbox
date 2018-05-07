#include <cstdio>
#include <cstring>
#include <ios>
#include <ostream>
#include <sstream>
#include <string>

#include "MacAddress.hpp"

//==============================================================================
// MacAddress constructor; initializes to all zeros
//==============================================================================
MacAddress::MacAddress()
{
    reserve(length);
}

//==============================================================================
// MacAddress constructor; initializes to match the given string
//==============================================================================
MacAddress::MacAddress(const std::string& mac_address_str)
{
    reserve(length);

    *this = mac_address_str;
}

//==============================================================================
// MacAddress copy constructor; copies the address of the given MAC address
//==============================================================================
MacAddress::MacAddress(const MacAddress& mac_address)
{
    reserve(length);

    *this = mac_address;
}

//==============================================================================
// MacAddress destructor; does nothing since no dynamic memory is allocated
//==============================================================================
MacAddress::~MacAddress()
{
}

//==============================================================================
// Writes string representation of self to the given string
//==============================================================================
bool MacAddress::toString(std::string& mac_address_str) const
{
    // 18 characters for the whole representation; 12 for the actual numbers, 5
    // for the colons in-between, and 1 on the end for the null
    char mac_cstr[18];
    mac_cstr[17] = 0;
    if (snprintf(mac_cstr,
                 18,
                 "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
                 at(0),
                 at(1),
                 at(2),
                 at(3),
                 at(4),
                 at(5)) < 0)
    {
        return false;
    }

    mac_address_str = mac_cstr;

    return true;
}

//==============================================================================
// Writes string representation of self to the ostream
//==============================================================================
std::ostream& operator<<(std::ostream& os, MacAddress& mac_address)
{
    std::string mac_address_str;
    if (!mac_address.toString(mac_address_str))
    {
        // Something bad happened, so set the fail bit on the stream
        os.setstate(std::ios_base::failbit);
    }

    return os << mac_address_str;
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

    int tempmac[MacAddress::length];
    // Scan the temporary string as a MAC address
    if (sscanf(tempstr,
               "%2x:%2x:%2x:%2x:%2x:%2x",
               &tempmac[0],
               &tempmac[1],
               &tempmac[2],
               &tempmac[3],
               &tempmac[4],
               &tempmac[5]) != MacAddress::length)
    {
        // We didn't convert all 6 bytes.  Leave our internal state as-is but
        // set the fail bit on the stream so the user has some way of knowing
        is.setstate(std::ios_base::failbit);
        return is;
    }

    // Copy from temporary storage into permanent storage
    for (unsigned int i = 0; i < MacAddress::length; i++)
    {
        mac_address.at(i) = static_cast<unsigned char>(tempmac[i]);
    }

    return is;
}
