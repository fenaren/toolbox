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
MacAddress::MacAddress(const char* mac_address_str)
{
    initialize();

    *this = mac_address_str;
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
    reserve(MAC_LENGTH_BYTES);
    assign(MAC_LENGTH_BYTES, 0);
}

//==============================================================================
// Writes string representation of self to the ostream
//==============================================================================
std::ostream& operator<<(std::ostream& os, MacAddress& mac_address)
{
    // 18 characters for the whole representation; 12 for the actual numbers, 5
    // for the colons in-between, and 1 on the end for the null
    char mac_cstr[MacAddress::MAC_MAX_STR_LENGTH_CHARS];
    mac_cstr[MacAddress::MAC_MAX_STR_LENGTH_CHARS - 1] = 0;
    if (snprintf(mac_cstr,
                 MacAddress::MAC_MAX_STR_LENGTH_CHARS,
                 "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
                 mac_address.at(0),
                 mac_address.at(1),
                 mac_address.at(2),
                 mac_address.at(3),
                 mac_address.at(4),
                 mac_address.at(5)) < 0)
    {
        // Something bad happened, so set the fail bit on the stream
        os.setstate(std::ios_base::failbit);
        return os;
    }

    return os << std::string(mac_cstr);
}

//==============================================================================
// Reads string representation of self from the istream
//==============================================================================
std::istream& operator>>(std::istream& is, MacAddress& mac_address)
{
    // Grab 17 characters from the stream and store temporarily; we use the
    // number 18 below because the istream get function reads the argument - 1
    char tempstr[MacAddress::MAC_MAX_STR_LENGTH_CHARS];
    is.get(tempstr, MacAddress::MAC_MAX_STR_LENGTH_CHARS);

    unsigned int tempmac[MacAddress::MAC_LENGTH_BYTES];
    // Scan the temporary string as a MAC address
    if (sscanf(tempstr,
               "%2x:%2x:%2x:%2x:%2x:%2x",
               &tempmac[0],
               &tempmac[1],
               &tempmac[2],
               &tempmac[3],
               &tempmac[4],
               &tempmac[5]) != MacAddress::MAC_LENGTH_BYTES)
    {
        // We didn't convert all 6 bytes.  Leave our internal state as-is but
        // set the fail bit on the stream so the user has some way of knowing
        is.setstate(std::ios_base::failbit);
        return is;
    }

    // Copy from temporary storage into permanent storage
    for (unsigned int i = 0; i < MacAddress::MAC_LENGTH_BYTES; i++)
    {
        mac_address.at(i) = static_cast<unsigned char>(tempmac[i]);
    }

    return is;
}

//==============================================================================
// Compares for equality with the given MAC address string
//==============================================================================
bool operator==(const std::string& mac_address_str,
                const MacAddress&  mac_address)
{
    return mac_address == mac_address_str;
}

//==============================================================================
// Compares for inequality with the given MAC address string
//==============================================================================
bool operator!=(const std::string& mac_address_str,
                const MacAddress&  mac_address)
{
    return !operator==(mac_address_str, mac_address);
}
