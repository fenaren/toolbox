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
MacAddress::MacAddress() :
    Data(mac_address, MacAddress::length)
{
}

//==============================================================================
// MacAddress constructor; initializes to match the given string
//==============================================================================
MacAddress::MacAddress(const std::string& mac_address_str) :
    Data(mac_address, MacAddress::length)
{
    *this = mac_address_str;
}

//==============================================================================
// MacAddress copy constructor; copies the address of the given MAC address
//==============================================================================
MacAddress::MacAddress(const MacAddress& mac_address) :
    Data(this->mac_address, MacAddress::length)
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
    memcpy(this->mac_address, mac_address.getData(), MacAddress::length);

    return *this;
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
// Allows the use of brackets to index into the MAC address
//==============================================================================
char& MacAddress::operator[](const unsigned int byteNum)
{
    return mac_address[byteNum];
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
                 mac_address[0],
                 mac_address[1],
                 mac_address[2],
                 mac_address[3],
                 mac_address[4],
                 mac_address[5]) < 0)
    {
        return false;
    }

    mac_address_str = mac_cstr;

    return true;
}

//==============================================================================
// Compares for equality with the given MAC address string
//==============================================================================
bool MacAddress::operator==(const MacAddress& mac_address) const
{
    return *dynamic_cast<const Data*>(this) == mac_address;
}

//==============================================================================
// Compares for equality with the given MAC address string
//==============================================================================
bool MacAddress::operator==(const std::string& mac_address_str) const
{
    return !operator==(MacAddress(mac_address_str));
}

//==============================================================================
// Compares for equality with the given MAC address string
//==============================================================================
bool MacAddress::operator!=(const MacAddress& mac_address) const
{
    return *dynamic_cast<const Data*>(this) != mac_address;
}

//==============================================================================
// Compares for inequality with the given MAC address string
//==============================================================================
bool MacAddress::operator!=(const std::string& mac_address_str) const
{
    return !operator==(mac_address_str);
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
        mac_address[i] = static_cast<unsigned char>(tempmac[i]);
    }

    return is;
}
