#include <cstdio>
#include <cstring>
#include <ios>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "MacAddress.hpp"

//==============================================================================
// MacAddress constructor; initializes to all zeros
//==============================================================================
MacAddress::MacAddress() :
    NetworkAddress(MAC_LENGTH_BYTES)
{
}

//==============================================================================
// MacAddress constructor; initializes to a copy of the data at the indicated
// location
//==============================================================================
MacAddress::MacAddress(const unsigned char* raw_address) :
    NetworkAddress(raw_address, MAC_LENGTH_BYTES)
{
}

//==============================================================================
// MacAddress constructor; initializes to match the given string
//==============================================================================
MacAddress::MacAddress(const std::string& mac_address_str) :
    NetworkAddress(MAC_LENGTH_BYTES)
{
    *this = mac_address_str;
}

//==============================================================================
// MacAddress copy constructor; copies the address of the given MAC address
//==============================================================================
MacAddress::MacAddress(const MacAddress& mac_address) :
    NetworkAddress(MAC_LENGTH_BYTES)
{
    *this = mac_address;
}

//==============================================================================
// Defines how to convert a MacAddress to a std::string
//==============================================================================
MacAddress::operator std::string() const
{
    std::ostringstream tempstream;
    tempstream << *this;
    return tempstream.str();
}

//==============================================================================
// MacAddress destructor; does nothing since no dynamic memory is allocated
//==============================================================================
MacAddress::~MacAddress()
{
}

//==============================================================================
// Assigns a string to a IPv4 address
//==============================================================================
MacAddress& MacAddress::operator=(const std::string& mac_address_str)
{
    std::istringstream tempstream(mac_address_str);
    tempstream >> *this;

    return *this;
}

//==============================================================================
// Writes string representation of self to the ostream
//==============================================================================
std::ostream& operator<<(std::ostream& os, const MacAddress& mac_address)
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
// Equality comparison, MacAddress == MacAddress
//==============================================================================
bool operator==(const MacAddress& mac_address1, const MacAddress& mac_address2)
{
    return !memcmp(&mac_address1.at(0),
                   &mac_address2.at(0),
                   MacAddress::MAC_LENGTH_BYTES);
}

//==============================================================================
// Equality comparison, MacAddress == std::string
//==============================================================================
bool operator==(const MacAddress& mac_address1, const std::string& mac_address2)
{
    return mac_address1 == MacAddress(mac_address2);
}

//==============================================================================
// Equality comparison, std::string == MacAddress
//==============================================================================
bool operator==(const std::string& mac_address1, const MacAddress& mac_address2)
{
    return MacAddress(mac_address1) == mac_address2;
}

//==============================================================================
// Inequality comparison, MacAddress != MacAddress
//==============================================================================
bool operator!=(const MacAddress& mac_address1, const MacAddress& mac_address2)
{
    return !(mac_address1 == mac_address2);
}

//==============================================================================
// Inequality comparison, MacAddress != std::string
//==============================================================================
bool operator!=(const MacAddress& mac_address1, const std::string& mac_address2)
{
    return !(mac_address1 == mac_address2);
}

//==============================================================================
// Inequality comparison, std::string != MacAddress
//==============================================================================
bool operator!=(const std::string& mac_address1, const MacAddress& mac_address2)
{
    return !(mac_address1 == mac_address2);
}
