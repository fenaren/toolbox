#include <cstdio>
#include <cstring>
#include <ios>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "MacAddress.hpp"

#include "RawDataField.hpp"
#include "misc.hpp"

//==============================================================================
MacAddress::MacAddress() :
    RawDataField(
        mac_address_raw, LENGTH_BYTES, misc::BYTES, false)
{
    memset(mac_address_raw, 0, LENGTH_BYTES);
}

//==============================================================================
// cppcheck-suppress uninitMemberVar
MacAddress::MacAddress(std::uint8_t* buffer) :
    MacAddress()
{
    DataField::readRaw(buffer);
}

//==============================================================================
MacAddress::MacAddress(const std::string& mac_address_str) :
    MacAddress()
{
    *this = mac_address_str;
}

//==============================================================================
// cppcheck-suppress uninitMemberVar
MacAddress::MacAddress(const MacAddress& mac_address) :
    RawDataField(mac_address)
{
}

//==============================================================================
MacAddress::~MacAddress()
{
}

//==============================================================================
MacAddress::operator std::string() const
{
    std::ostringstream tempstream;
    tempstream << *this;
    return tempstream.str();
}

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
        RawDataField::operator=(mac_address);
    }

    return *this;
}

//==============================================================================
std::ostream& operator<<(std::ostream& os, const MacAddress& mac_address)
{
    // 18 characters for the whole representation; 12 for the actual numbers, 5
    // for the colons in-between, and 1 on the end for the null
    char mac_cstr[MacAddress::MAX_STR_LENGTH_CHARS];
    mac_cstr[MacAddress::MAX_STR_LENGTH_CHARS - 1] = 0;
    if (snprintf(mac_cstr,
                 MacAddress::MAX_STR_LENGTH_CHARS,
                 "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
                 mac_address.getByte(0),
                 mac_address.getByte(1),
                 mac_address.getByte(2),
                 mac_address.getByte(3),
                 mac_address.getByte(4),
                 mac_address.getByte(5)) < 0)
    {
        // Something bad happened, so set the fail bit on the stream
        os.setstate(std::ios_base::failbit);
        return os;
    }

    return os << std::string(mac_cstr);
}

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
bool operator==(const MacAddress& lhs, const MacAddress& rhs)
{
    return static_cast<RawDataField>(lhs) ==
        static_cast<RawDataField>(rhs);
}

//==============================================================================
bool operator==(const MacAddress& lhs, const std::string& rhs)
{
    return static_cast<RawDataField>(lhs) ==
        static_cast<RawDataField>(MacAddress(rhs));
}

//==============================================================================
bool operator==(const std::string& lhs, const MacAddress& rhs)
{
    return static_cast<RawDataField>(MacAddress(lhs)) ==
        static_cast<RawDataField>(rhs);
}

//==============================================================================
bool operator!=(const MacAddress& lhs, const MacAddress& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
bool operator!=(const MacAddress& lhs, const std::string& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
bool operator!=(const std::string& lhs, const MacAddress& rhs)
{
    return !(lhs == rhs);
}
