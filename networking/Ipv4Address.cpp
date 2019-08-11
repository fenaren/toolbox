#include <cstdio>
#include <cstring>
#include <ios>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "Ipv4Address.hpp"

#include "RawDataField.hpp"
#include "misc.hpp"

//==============================================================================
Ipv4Address::Ipv4Address() :
    RawDataField(ipv4_address_raw, LENGTH_BYTES, misc::BYTES, false)
{
    memset(ipv4_address_raw, 0, LENGTH_BYTES);
}

//==============================================================================
// cppcheck-suppress uninitMemberVar
Ipv4Address::Ipv4Address(std::uint8_t* buffer) :
    Ipv4Address()
{
    DataField::readRaw(buffer);
}

//==============================================================================
Ipv4Address::Ipv4Address(const std::string& ipv4_address_str) :
    Ipv4Address()
{
    *this = ipv4_address_str;
}

//==============================================================================
// cppcheck-suppress uninitMemberVar
Ipv4Address::Ipv4Address(const Ipv4Address& ipv4_address) :
    RawDataField(ipv4_address)
{
}

//==============================================================================
Ipv4Address::operator std::string() const
{
    std::ostringstream tempstream;
    tempstream << *this;
    return tempstream.str();
}

//==============================================================================
Ipv4Address::~Ipv4Address()
{
}

//==============================================================================
Ipv4Address& Ipv4Address::operator=(const std::string& ipv4_address_str)
{
    std::istringstream tempstream(ipv4_address_str);
    tempstream >> *this;

    return *this;
}

//==============================================================================
Ipv4Address& Ipv4Address::operator=(const Ipv4Address& ipv4_address)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &ipv4_address)
    {
        // Use the parent class operator=
        RawDataField::operator=(ipv4_address);
    }

    return *this;
}

//==============================================================================
std::ostream& operator<<(std::ostream& os, const Ipv4Address& ipv4_address)
{
    // 16 characters for the whole representation; 12 for the actual numbers, 3
    // for the periods in-between, and 1 on the end for the null
    char ipv4_cstr[Ipv4Address::MAX_STR_LENGTH_CHARS];
    ipv4_cstr[Ipv4Address::MAX_STR_LENGTH_CHARS - 1] = 0;
    if (snprintf(ipv4_cstr,
                 Ipv4Address::MAX_STR_LENGTH_CHARS,
                 "%hhu.%hhu.%hhu.%hhu",
                 ipv4_address.getByte(0),
                 ipv4_address.getByte(1),
                 ipv4_address.getByte(2),
                 ipv4_address.getByte(3)) < 0)
    {
        // Something bad happened, so set the fail bit on the stream
        os.setstate(std::ios_base::failbit);
        return os;
    }

    return os << std::string(ipv4_cstr);
}

//==============================================================================
std::istream& operator>>(std::istream& is, Ipv4Address& ipv4_address)
{
    // Grab characters from the stream and store temporarily
    char tempstr[Ipv4Address::MAX_STR_LENGTH_CHARS];
    is.get(tempstr, Ipv4Address::MAX_STR_LENGTH_CHARS);

    unsigned int tempipv4[Ipv4Address::LENGTH_BYTES];
    // Scan the temporary string as a IPv4 address
    if (std::sscanf(tempstr,
                    "%u.%u.%u.%u",
                    &tempipv4[0],
                    &tempipv4[1],
                    &tempipv4[2],
                    &tempipv4[3]) != Ipv4Address::LENGTH_BYTES)
    {
        // We didn't convert all 4 bytes.  Leave our internal state as-is but
        // set the fail bit on the stream so the user has some way of knowing
        is.setstate(std::ios_base::failbit);
        return is;
    }

    // Copy from temporary storage into permanent storage
    for (unsigned int i = 0; i < Ipv4Address::LENGTH_BYTES; i++)
    {
        ipv4_address.setByte(i, tempipv4[i]);
    }

    return is;
}

//==============================================================================
bool operator==(const Ipv4Address& lhs, const Ipv4Address& rhs)
{
    return static_cast<RawDataField>(lhs) == static_cast<RawDataField>(rhs);
}

//==============================================================================
bool operator==(const Ipv4Address& lhs, const std::string& rhs)
{
    return static_cast<RawDataField>(lhs) ==
        static_cast<RawDataField>(Ipv4Address(rhs));
}

//==============================================================================
bool operator==(const std::string& lhs, const Ipv4Address& rhs)
{
    return static_cast<RawDataField>(Ipv4Address(lhs)) ==
        static_cast<RawDataField>(rhs);
}

//==============================================================================
bool operator!=(const Ipv4Address& lhs, const Ipv4Address& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
bool operator!=(const Ipv4Address& lhs, const std::string& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
bool operator!=(const std::string& lhs, const Ipv4Address& rhs)
{
    return !(lhs == rhs);
}
