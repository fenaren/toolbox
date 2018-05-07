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
    initialize();
}

//==============================================================================
// MacAddress constructor; initializes to match the given string
//==============================================================================
MacAddress::MacAddress(const std::string& mac_address_str)
{
    initialize();

    *this = mac_address_str;
}

//==============================================================================
// MacAddress copy constructor; copies the address of the given MAC address
//==============================================================================
MacAddress::MacAddress(const MacAddress& mac_address)
{
    initialize();

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
    char mac_cstr[MAC_STR_LENGTH];
    mac_cstr[MAC_STR_LENGTH - 1] = 0;
    if (snprintf(mac_cstr,
                 MAC_STR_LENGTH,
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
// Assigns a string to a MAC address
//==============================================================================
MacAddress& MacAddress::operator=(const std::string& mac_address_str)
{
    std::istringstream tempstream(mac_address_str);
    tempstream >> *this;

    return *this;
}

//==============================================================================
// Compares for equality with the given MAC address string
//==============================================================================
bool MacAddress::operator==(const std::string& mac_address_str) const
{
    return *this == MacAddress(mac_address_str);
}

//==============================================================================
// Compares for inequality with the given MAC address string
//==============================================================================
bool MacAddress::operator!=(const std::string& mac_address_str) const
{
    return !operator==(mac_address_str);
}

//==============================================================================
//
//==============================================================================
void MacAddress::initialize()
{
    reserve(MAC_LENGTH);
    assign(MAC_LENGTH, 0);
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
    char tempstr[MacAddress::MAC_STR_LENGTH];
    is.get(tempstr, MacAddress::MAC_STR_LENGTH);

    int tempmac[MacAddress::MAC_LENGTH];
    // Scan the temporary string as a MAC address
    if (sscanf(tempstr,
               "%2x:%2x:%2x:%2x:%2x:%2x",
               &tempmac[0],
               &tempmac[1],
               &tempmac[2],
               &tempmac[3],
               &tempmac[4],
               &tempmac[5]) != MacAddress::MAC_LENGTH)
    {
        // We didn't convert all 6 bytes.  Leave our internal state as-is but
        // set the fail bit on the stream so the user has some way of knowing
        is.setstate(std::ios_base::failbit);
        return is;
    }

    // Copy from temporary storage into permanent storage
    for (unsigned int i = 0; i < MacAddress::MAC_LENGTH; i++)
    {
        mac_address.at(i) = static_cast<unsigned char>(tempmac[i]);
    }

    return is;
}
