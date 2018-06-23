#include <cstdio>
#include <cstring>
#include <ios>
#include <ostream>
#include <sstream>
#include <string>

#include "Ipv4Address.hpp"

//==============================================================================
// Ipv4Address constructor; initializes to all zeros
//==============================================================================
Ipv4Address::Ipv4Address()
{
    initialize();
}

//==============================================================================
// Ipv4Address constructor; initializes to match the given string
//==============================================================================
Ipv4Address::Ipv4Address(const char* ipv4_address_str)
{
    initialize();

    *this = ipv4_address_str;
}

//==============================================================================
// Ipv4Address constructor; initializes to match the given string
//==============================================================================
Ipv4Address::Ipv4Address(const std::string& ipv4_address_str)
{
    initialize();

    *this = ipv4_address_str;
}

//==============================================================================
// Ipv4Address copy constructor; copies the address of the given IPv4 address
//==============================================================================
Ipv4Address::Ipv4Address(const Ipv4Address& ipv4_address)
{
    initialize();

    *this = ipv4_address;
}

//==============================================================================
// Ipv4Address destructor; does nothing since no dynamic memory is allocated
//==============================================================================
Ipv4Address::~Ipv4Address()
{
}

//==============================================================================
// Writes string representation of self to the given string
//==============================================================================
bool Ipv4Address::toString(std::string& ipv4_address_str) const
{
    // 16 characters for the whole representation; 12 for the actual numbers, 3
    // for the periods in-between, and 1 on the end for the null
    char ipv4_cstr[IPV4_MAX_STR_LENGTH_CHARS];
    ipv4_cstr[IPV4_MAX_STR_LENGTH_CHARS - 1] = 0;
    if (snprintf(ipv4_cstr,
                 IPV4_MAX_STR_LENGTH_CHARS,
                 "%hhu.%hhu.%hhu.%hhu",
                 at(0),
                 at(1),
                 at(2),
                 at(3)) < 0)
    {
        return false;
    }

    ipv4_address_str = ipv4_cstr;

    return true;
}

//==============================================================================
// Assigns a string to a IPv4 address
//==============================================================================
Ipv4Address& Ipv4Address::operator=(const std::string& ipv4_address_str)
{
    std::istringstream tempstream(ipv4_address_str);
    tempstream >> *this;

    return *this;
}

//==============================================================================
// Compares for equality with the given IPv4 address string
//==============================================================================
bool Ipv4Address::operator==(const std::string& ipv4_address_str) const
{
    return *this == Ipv4Address(ipv4_address_str);
}

//==============================================================================
// Compares for inequality with the given IPv4 address string
//==============================================================================
bool Ipv4Address::operator!=(const std::string& ipv4_address_str) const
{
    return !operator==(ipv4_address_str);
}

//==============================================================================
//
//==============================================================================
void Ipv4Address::initialize()
{
    reserve(IPV4_LENGTH_BYTES);
    assign(IPV4_LENGTH_BYTES, 0);
}

//==============================================================================
// Writes string representation of self to the ostream
//==============================================================================
std::ostream& operator<<(std::ostream& os, Ipv4Address& ipv4_address)
{
    std::string ipv4_address_str;
    if (!ipv4_address.toString(ipv4_address_str))
    {
        // Something bad happened, so set the fail bit on the stream
        os.setstate(std::ios_base::failbit);
    }

    return os << ipv4_address_str;
}

//==============================================================================
// Reads string representation of self from the istream
//==============================================================================
std::istream& operator>>(std::istream& is, Ipv4Address& ipv4_address)
{
    // Grab characters from the stream and store temporarily
    char tempstr[Ipv4Address::IPV4_MAX_STR_LENGTH_CHARS];
    is.get(tempstr, Ipv4Address::IPV4_MAX_STR_LENGTH_CHARS);

    int tempipv4[Ipv4Address::IPV4_LENGTH_BYTES];
    // Scan the temporary string as a IPv4 address
    if (sscanf(tempstr,
               "%u.%u.%u.%u",
               &tempipv4[0],
               &tempipv4[1],
               &tempipv4[2],
               &tempipv4[3]) != Ipv4Address::IPV4_LENGTH_BYTES)
    {
        // We didn't convert all 4 bytes.  Leave our internal state as-is but
        // set the fail bit on the stream so the user has some way of knowing
        is.setstate(std::ios_base::failbit);
        return is;
    }

    // Copy from temporary storage into permanent storage
    for (unsigned int i = 0; i < Ipv4Address::IPV4_LENGTH_BYTES; i++)
    {
        ipv4_address.at(i) = static_cast<unsigned char>(tempipv4[i]);
    }

    return is;
}

//==============================================================================
// Compares for equality with the given IPv4 address string
//==============================================================================
bool operator==(const std::string& ipv4_address_str,
                const Ipv4Address& ipv4_address)
{
    return ipv4_address == ipv4_address_str;
}

//==============================================================================
// Compares for inequality with the given IPv4 address string
//==============================================================================
bool operator!=(const std::string& ipv4_address_str,
                const Ipv4Address& ipv4_address)
{
    return !operator==(ipv4_address_str, ipv4_address);
}
