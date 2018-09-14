#include <cstdio>
#include <cstring>
#include <ios>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "Ipv4Address.hpp"

//==============================================================================
// Does nothing
//==============================================================================
Ipv4Address::Ipv4Address() :
    Data(4, 16)
{
}

//==============================================================================
// A shortcut to read()
//==============================================================================
Ipv4Address::Ipv4Address(unsigned char* buf) :
    Data(4, 16)
{
    read(buf);
}

//==============================================================================
// Initializes to match the given string
//==============================================================================
Ipv4Address::Ipv4Address(const std::string& ipv4_address_str) :
    Data(4, 16)
{
    *this = ipv4_address_str;
}

//==============================================================================
// Copy constructor; copies the address of the given IPv4 address
//==============================================================================
Ipv4Address::Ipv4Address(const Ipv4Address& ipv4_address) :
    Data(4, 16)
{
    *this = ipv4_address;
}

//==============================================================================
// Does nothing, obviously
//==============================================================================
Ipv4Address::~Ipv4Address()
{
}

//==============================================================================
void Ipv4Address::read(unsigned char* buffer)
{
    for (unsigned int i = 0; i < LENGTH_BYTES; i++)
    {
        octets[i] = static_cast<unsigned int>(*buffer);
    }
}

//==============================================================================
void Ipv4Address::write(unsigned char* buffer) const
{
    for (unsigned int i = 0; i < LENGTH_BYTES; i++)
    {
        *buffer = static_cast<unsigned char>(octets[i]);
    }
}

//==============================================================================
// Allows a user to set a particular octet, numbered 0-3
//==============================================================================
void Ipv4Address::setOctet(unsigned int octet, unsigned int value)
{
    if (octet >= LENGTH_BYTES)
    {
        std::ostringstream error_stream;
        error_stream << "Out-of-range octet (" << octet << " specified, "
                     << LENGTH_BYTES - 1 << " max)";

        throw std::out_of_range(error_stream.str());
    }
    else if (value > MAX_OCTET_VALUE)
    {
        std::ostringstream error_stream;
        error_stream << "Invalid octet value (" << value << " specified, "
                  << MAX_OCTET_VALUE << " max)\n";

        throw std::invalid_argument(error_stream.str());
    }

    octets[octet] = value;
}

//==============================================================================
// Allows a user to get the value of a particular octet, numbered 0-3
//==============================================================================
unsigned int Ipv4Address::getOctet(unsigned int octet) const
{
    if (octet >= LENGTH_BYTES)
    {
        std::ostringstream error_stream;
        error_stream << "Out-of-range octet (" << octet << " specified, "
                     << LENGTH_BYTES - 1 << " max)";

        throw std::out_of_range(error_stream.str());
    }

    return octets[octet];
}

//==============================================================================
// Defines how to convert a MacAddress to a std::string
//==============================================================================
Ipv4Address::operator std::string() const
{
    std::ostringstream tempstream;
    tempstream << *this;
    return tempstream.str();
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
// Writes string representation of self to the ostream
//==============================================================================
std::ostream& operator<<(std::ostream& os, const Ipv4Address& ipv4_address)
{
    // 16 characters for the whole representation; 12 for the actual numbers, 3
    // for the periods in-between, and 1 on the end for the null
    char ipv4_cstr[Ipv4Address::MAX_STR_LENGTH_CHARS];
    memset(ipv4_cstr, 0, Ipv4Address::MAX_STR_LENGTH_CHARS);

    if (snprintf(ipv4_cstr,
                 Ipv4Address::MAX_STR_LENGTH_CHARS,
                 "%hhu.%hhu.%hhu.%hhu",
                 static_cast<unsigned char>(ipv4_address.getOctet(0)),
                 static_cast<unsigned char>(ipv4_address.getOctet(1)),
                 static_cast<unsigned char>(ipv4_address.getOctet(2)),
                 static_cast<unsigned char>(ipv4_address.getOctet(3))) < 0)
    {
        // Something bad happened, so set the fail bit on the stream
        os.setstate(std::ios_base::failbit);
        return os;
    }

    return os << std::string(ipv4_cstr);
}

//==============================================================================
// Reads string representation of self from the istream
//==============================================================================
std::istream& operator>>(std::istream& is, Ipv4Address& ipv4_address)
{
    // Grab what is hopefully a string representation of an IPv4 address
    std::string tempstr;
    is >> tempstr;

    unsigned int tempipv4[Ipv4Address::LENGTH_BYTES];
    // Scan the temporary string as a IPv4 address
    if (sscanf(tempstr.c_str(),
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
        ipv4_address.setOctet(i, tempipv4[i]);
    }

    return is;
}

//==============================================================================
// Equality comparison, Ipv4Address == Ipv4Address
//==============================================================================
bool
operator==(const Ipv4Address& ipv4_address1, const Ipv4Address& ipv4_address2)
{
    return ipv4_address1.getOctet(1) == ipv4_address2.getOctet(1) &&
        ipv4_address1.getOctet(2) == ipv4_address2.getOctet(2) &&
        ipv4_address1.getOctet(3) == ipv4_address2.getOctet(3) &&
        ipv4_address1.getOctet(4) == ipv4_address2.getOctet(4);
}

//==============================================================================
// Equality comparison, Ipv4Address == std::string
//==============================================================================
bool
operator==(const Ipv4Address& ipv4_address1, const std::string& ipv4_address2)
{
    return ipv4_address1 == Ipv4Address(ipv4_address2);
}

//==============================================================================
// Equality comparison, std::string == Ipv4Address
//==============================================================================
bool
operator==(const std::string& ipv4_address1, const Ipv4Address& ipv4_address2)
{
    return Ipv4Address(ipv4_address1) == ipv4_address2;
}

//==============================================================================
// Inequality comparison, Ipv4Address != Ipv4Address
//==============================================================================
bool
operator!=(const Ipv4Address& ipv4_address1, const Ipv4Address& ipv4_address2)
{
    return !(ipv4_address1 == ipv4_address2);
}

//==============================================================================
// Inequality comparison, Ipv4Address != std::string
//==============================================================================
bool
operator!=(const Ipv4Address& ipv4_address1, const std::string& ipv4_address2)
{
    return !(ipv4_address1 == ipv4_address2);
}

//==============================================================================
// Inequality comparison, std::string != Ipv4Address
//==============================================================================
bool
operator!=(const std::string& ipv4_address1, const Ipv4Address& ipv4_address2)
{
    return !(ipv4_address1 == ipv4_address2);
}
