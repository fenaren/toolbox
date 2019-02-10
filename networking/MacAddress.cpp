#include <cstdio>
#include <cstring>
#include <ios>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "MacAddress.hpp"

#include "ByteField.hpp"

//==============================================================================
// MacAddress constructor; initializes to all zeros
//==============================================================================
MacAddress::MacAddress() :
    ByteField(mac_address_raw, LENGTH_BYTES, false)
{
    memset(mac_address_raw, 0, LENGTH_BYTES);
}

//==============================================================================
// MacAddress constructor; initializes to a copy of the data at the indicated
// location
//==============================================================================
// cppcheck-suppress uninitMemberVar
MacAddress::MacAddress(std::uint8_t* buffer) :
    ByteField(mac_address_raw, LENGTH_BYTES, false)
{
    readRaw(buffer);
}

//==============================================================================
// MacAddress constructor; initializes to match the given string
//==============================================================================
MacAddress::MacAddress(const std::string& mac_address_str) :
    ByteField(mac_address_raw, LENGTH_BYTES, false)
{
    *this = mac_address_str;
}

//==============================================================================
// cppcheck-suppress uninitMemberVar
MacAddress::MacAddress(const MacAddress& mac_address) :
    ByteField(mac_address)
{
}

//==============================================================================
// MacAddress destructor; does nothing since no dynamic memory is allocated
//==============================================================================
MacAddress::~MacAddress()
{
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
// Assigns a string to a IPv4 address
//==============================================================================
MacAddress& MacAddress::operator=(const std::string& mac_address_str)
{
    std::istringstream tempstream(mac_address_str);
    tempstream >> *this;

    return *this;
}

//==============================================================================
MacAddress& MacAddress::operator=(const MacAddress& mac_address)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &mac_address)
    {
        ByteField::operator=(mac_address);
    }

    return *this;
}

//==============================================================================
// Writes string representation of self to the ostream
//==============================================================================
std::ostream& operator<<(std::ostream& os, const MacAddress& mac_address)
{
    // 18 characters for the whole representation; 12 for the actual numbers, 5
    // for the colons in-between, and 1 on the end for the null
    char mac_cstr[MacAddress::MAX_STR_LENGTH_CHARS];
    mac_cstr[MacAddress::MAX_STR_LENGTH_CHARS - 1] = 0;
/*    if (snprintf(mac_cstr,
                 MacAddress::MAX_STR_LENGTH_CHARS,
                 "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
                 mac_address.getOctet(0),
                 mac_address.getOctet(1),
                 mac_address.getOctet(2),
                 mac_address.getOctet(3),
                 mac_address.getOctet(4),
                 mac_address.getOctet(5)) < 0)
    {
        // Something bad happened, so set the fail bit on the stream
        os.setstate(std::ios_base::failbit);
        return os;
        }*/

    return os << std::string(mac_cstr);
}

//==============================================================================
// Reads string representation of self from the istream
//==============================================================================
std::istream& operator>>(std::istream& is, MacAddress& mac_address)
{
    // Grab 17 characters from the stream and store temporarily; we use the
    // number 18 below because the istream get function reads the argument - 1
    char tempstr[MacAddress::MAX_STR_LENGTH_CHARS];
    is.get(tempstr, MacAddress::MAX_STR_LENGTH_CHARS);

    unsigned int tempmac[MacAddress::LENGTH_BYTES];
    // Scan the temporary string as a MAC address
    if (sscanf(tempstr,
               "%2x:%2x:%2x:%2x:%2x:%2x",
               &tempmac[0],
               &tempmac[1],
               &tempmac[2],
               &tempmac[3],
               &tempmac[4],
               &tempmac[5]) != MacAddress::LENGTH_BYTES)
    {
        // We didn't convert all 6 bytes.  Leave our internal state as-is but
        // set the fail bit on the stream so the user has some way of knowing
        is.setstate(std::ios_base::failbit);
        return is;
    }

    // Copy from temporary storage into permanent storage
    for (unsigned int i = 0; i < MacAddress::LENGTH_BYTES; i++)
    {
        mac_address.setByte(i, tempmac[i]);
    }

    return is;
}

//==============================================================================
// Equality comparison, MacAddress == MacAddress
//==============================================================================
bool operator==(const MacAddress& mac_address1, const MacAddress& mac_address2)
{
    return static_cast<ByteField>(mac_address1) ==
        static_cast<ByteField>(mac_address2);
}

//==============================================================================
// Equality comparison, MacAddress == MacAddress
//==============================================================================
bool operator==(const MacAddress& mac_address1, const std::string& mac_address2)
{
    return static_cast<ByteField>(mac_address1) ==
        static_cast<ByteField>(MacAddress(mac_address2));
}

//==============================================================================
// Equality comparison, std::string == MacAddress
//==============================================================================
bool operator==(const std::string& mac_address1, const MacAddress& mac_address2)
{
    return static_cast<ByteField>(MacAddress(mac_address1)) ==
        static_cast<ByteField>(mac_address2);
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
